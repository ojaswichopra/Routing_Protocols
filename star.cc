#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h" // For NetAnim

using namespace ns3;

int main (int argc, char *argv[])
{
  uint32_t numLeafNodes = 5; // Number of leaf nodes in the star topology
  CommandLine cmd;
  cmd.AddValue ("numLeafNodes", "Number of leaf nodes in the star topology", numLeafNodes);
  cmd.Parse (argc, argv);

  // Create node containers for central node (hub) and leaf nodes
  NodeContainer hubNode;
  hubNode.Create (1); // Single hub node

  NodeContainer leafNodes;
  leafNodes.Create (numLeafNodes); // Leaf nodes

  // Point-to-Point link configuration
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  // Install Internet Stack (TCP/IP) on all nodes
  InternetStackHelper internet;
  internet.Install (hubNode);
  internet.Install (leafNodes);

  // Create and install point-to-point devices and interfaces
  Ipv4AddressHelper address;
  NetDeviceContainer devices;
  Ipv4InterfaceContainer interfaces;

  for (uint32_t i = 0; i < numLeafNodes; ++i)
  {
    // Create point-to-point links between the hub and each leaf node
    NodeContainer hubToLeaf (hubNode.Get (0), leafNodes.Get (i));
    devices = pointToPoint.Install (hubToLeaf);

    // Assign IP addresses to each link
    std::ostringstream subnet;
    subnet << "10.1." << i + 1 << ".0";
    address.SetBase (subnet.str ().c_str (), "255.255.255.0");
    interfaces.Add (address.Assign (devices));
  }

  // Install a UDP Echo Server on the hub node
  UdpEchoServerHelper echoServer (9); // Port number 9
  ApplicationContainer serverApp = echoServer.Install (hubNode.Get (0));
  serverApp.Start (Seconds (1.0));
  serverApp.Stop (Seconds (10.0));

  // Install a UDP Echo Client on each leaf node to send data to the hub node
  for (uint32_t i = 0; i < numLeafNodes; ++i)
  {
    UdpEchoClientHelper echoClient (interfaces.GetAddress (0), 9); // Send to hub node
    echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
    echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
    echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

    ApplicationContainer clientApp = echoClient.Install (leafNodes.Get (i));
    clientApp.Start (Seconds (2.0));
    clientApp.Stop (Seconds (10.0));
  }

  // Enable NetAnim to capture the simulation
  AnimationInterface anim ("star_topology.xml");

  // Set positions for nodes in NetAnim visualization
  anim.SetConstantPosition (hubNode.Get (0), 50, 50); // Hub node at the center
  for (uint32_t i = 0; i < numLeafNodes; ++i)
  {
    double angle = 2 * M_PI * i / numLeafNodes;
    double x = 50 + 30 * std::cos (angle);
    double y = 50 + 30 * std::sin (angle);
    anim.SetConstantPosition (leafNodes.Get (i), x, y); // Arrange leaf nodes in a circle
  }

  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}
