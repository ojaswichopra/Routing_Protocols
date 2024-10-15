#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/olsr-helper.h"
#include "ns3/aodv-helper.h"
#include "ns3/dsdv-helper.h"
#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/udp-echo-helper.h" 
#include <fstream>  // For CSV file output
#include <cstdlib>  // For rand()
#include <ctime> 

using namespace ns3;

void SetupTraffic (Ptr<Node> source, Ptr<Node> dest, uint16_t port) {
    UdpEchoServerHelper echoServer (port);
    ApplicationContainer serverApp = echoServer.Install (dest);
    serverApp.Start (Seconds (1.0));
    serverApp.Stop (Seconds (10.0));

    UdpEchoClientHelper echoClient (dest->GetObject<Ipv4>()->GetAddress (1, 0).GetLocal (), port);
    echoClient.SetAttribute ("MaxPackets", UintegerValue (10));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (1024));
    
    ApplicationContainer clientApp = echoClient.Install (source);
    clientApp.Start (Seconds (2.0));
    clientApp.Stop (Seconds (10.0));
}

void SaveResultsToCsv (std::string filename, const std::map<FlowId, FlowMonitor::FlowStats>& stats, 
                       Ptr<Ipv4FlowClassifier> classifier) {
    std::ofstream csvFile;
    csvFile.open (filename, std::ios::out | std::ios::app);  // Open in append mode

    csvFile << "FlowID,Source,Destination,TxBytes,RxBytes,Throughput(Mbps),PacketDeliveryRatio(%),"
            << "EndToEndDelay(ms),PacketsDropped,Jitter(ms)\n";

    for (const auto& stat : stats) {
        Ipv4FlowClassifier::FiveTuple t = classifier->FindFlow (stat.first);
        
        double throughput = (stat.second.rxBytes * 8.0) / 
                            (stat.second.timeLastRxPacket.GetSeconds() - stat.second.timeFirstTxPacket.GetSeconds()) / 1000 / 1000;  // Mbps
        
        double packetDeliveryRatio = (stat.second.rxPackets / (double)stat.second.txPackets) * 100.0;
        
        double endToEndDelay = (stat.second.delaySum.GetSeconds() / stat.second.rxPackets) * 1000;  // Convert to ms
        
        uint32_t packetsDropped = stat.second.lostPackets;
        
        double jitter = (stat.second.jitterSum.GetSeconds() / stat.second.rxPackets) * 1000;  // Convert to ms
        
        csvFile << stat.first << "," 
                << t.sourceAddress << "," 
                << t.destinationAddress << ","
                << stat.second.txBytes << "," 
                << stat.second.rxBytes << ","
                << throughput << "," 
                << packetDeliveryRatio << ","
                << endToEndDelay << ","
                << packetsDropped << ","
                << jitter << "\n";
    }

    csvFile.close ();
}


int main (int argc, char *argv[]) {
    std::string protocol = "OLSR";
    std::string topology = "star";
    std::string outputFile = "results.csv";  // CSV output file

    CommandLine cmd;
    cmd.AddValue ("protocol", "Routing protocol to use (OLSR, AODV, DSDV)", protocol);
    cmd.AddValue ("topology", "Topology to use (star, mesh)", topology);
    cmd.AddValue ("outputFile", "CSV file to store results", outputFile);
    cmd.Parse (argc, argv);

    NodeContainer routers;
    routers.Create (3);  // Create 3 routers
    NodeContainer peers;
    peers.Create (6);  // Create 6 peers

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
    p2p.SetChannelAttribute ("Delay", StringValue ("2ms"));

    InternetStackHelper internet;
    if (protocol == "OLSR") {
        OlsrHelper olsr;
        internet.SetRoutingHelper (olsr);
    } else if (protocol == "AODV") {
        AodvHelper aodv;
        internet.SetRoutingHelper (aodv);
    } else if (protocol == "DSDV") {
        DsdvHelper dsdv;
        internet.SetRoutingHelper (dsdv);
    }
    internet.Install (routers);
    internet.Install (peers);

    Ipv4AddressHelper address;
    address.SetBase ("10.1.1.0", "255.255.255.0");

    NetDeviceContainer devices;

    // Create Star Topology for Routers
    if (topology == "star") {
        for (uint32_t i = 0; i < peers.GetN (); ++i) {
            devices = p2p.Install (routers.Get(0), peers.Get(i));
            address.Assign (devices);
            address.NewNetwork ();
        }

    // Connect routers to each other
    devices = p2p.Install (routers.Get(0), routers.Get(1));
    address.Assign (devices);
    address.NewNetwork ();

    devices = p2p.Install (routers.Get(1), routers.Get(2));
    address.Assign (devices);
    address.NewNetwork ();

    // Optionally, connect more peers to other routers
    	for (uint32_t i = 0; i < 3; ++i) {
        	devices = p2p.Install (routers.Get(1), peers.Get(i + 3)); // Connect some peers to Router 2
	        address.Assign (devices);
	        address.NewNetwork ();
	    }
 	devices = p2p.Install (routers.Get(2), peers.Get(5)); // Connect some peers to Router 2
       	address.Assign (devices);
	address.NewNetwork ();
    }
    // Create Mesh Topology for Peers
    else if (topology == "mesh") {
        for (uint32_t i = 0; i < peers.GetN (); ++i) {
            for (uint32_t j = i + 1; j < peers.GetN (); ++j) {
                devices = p2p.Install (peers.Get(i), peers.Get(j));
                address.Assign (devices);
                address.NewNetwork ();
            }
        }
	srand(time(0));  // Seed the random number generator
        for (uint32_t i = 0; i < 3; ++i) {  // Create 3 random connections
            int peerIndex = rand() % peers.GetN();
            int routerIndex = rand() % routers.GetN();
            devices = p2p.Install(peers.Get(peerIndex), routers.Get(routerIndex));
            address.Assign(devices);
            address.NewNetwork();
        }

	// Connect Routers with each other (Optional for better visualization)
	for (uint32_t i = 0; i < routers.GetN(); ++i) {
  	    for (uint32_t j = i + 1; j < routers.GetN(); ++j) {
           	 devices = p2p.Install(routers.Get(i), routers.Get(j));
           	 address.Assign(devices);
           	 address.NewNetwork();
       	    }
   	}
    }

    SetupTraffic (peers.Get (0), peers.Get (5), 9); // Set up traffic between first two peers

    FlowMonitorHelper flowmon;
    Ptr<FlowMonitor> monitor = flowmon.InstallAll ();

    AnimationInterface anim ("protocol-comparison.xml");
    // Set colors for routers and peers through the XML file
    for (uint32_t i = 0; i < routers.GetN(); ++i) {
        anim.UpdateNodeDescription(routers.Get(i)->GetId(), "Router " + std::to_string(i + 1));  // Add description
        anim.UpdateNodeColor(routers.Get(i)->GetId(), 255, 0, 0);  // Set color as red (for routers)
    }
    
    for (uint32_t i = 0; i < peers.GetN(); ++i) {
        anim.UpdateNodeDescription(peers.Get(i)->GetId(), "Peer " + std::to_string(i + 1));  // Add description
        anim.UpdateNodeColor(peers.Get(i)->GetId(), 0, 255, 0);  // Set color as green (for peers)
    }

    Simulator::Stop (Seconds (10.0));
    Simulator::Run ();

    monitor->CheckForLostPackets ();
    Ptr<Ipv4FlowClassifier> classifier = DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier ());
    std::map<FlowId, FlowMonitor::FlowStats> stats = monitor->GetFlowStats ();

    SaveResultsToCsv (outputFile, stats, classifier);

    Simulator::Destroy ();
    return 0;
}
