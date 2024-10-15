# Network Simulation using NS-3

This project involves creating a simulation of a network topology to analyze the performance of various routing algorithms or network protocols. The simulation is built using NS-3, a discrete-event network simulator, and focuses on evaluating the efficiency and reliability of different routing techniques in networking.

## Table of Contents

- [Description](#description)
- [Skills](#skills)
- [Tools](#tools)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Performance Metrics](#performance)
- [Contributing](#contributing)
- [License](#license)

## Description

In this project, we simulate network topologies and evaluate the performance of different routing algorithms or network protocols using NS-3. The objective is to gain insights into how different protocols perform in various scenarios, including throughput, latency, and packet loss. This helps in understanding the behavior of networking components in real-world situations.

The simulation can be adapted to compare multiple routing algorithms such as:

- **AODV (Ad-hoc On-demand Distance Vector)**  
- **OLSR (Optimized Link State Routing)**  
- **DSDV (Distance Sequenced Distance Vector)**  

The results of these simulations can be used for performance analysis and protocol optimization.

## Skills

To successfully work on this project, the following skills are required:

- **Knowledge of Routing Algorithms**: Understanding different network routing algorithms such as DSDV, AODV, OLSR, etc.
- **Network Simulation**: Familiarity with creating and running network simulations using NS-3.
- **Performance Analysis**: Ability to analyze metrics like throughput, delay, and packet loss to compare network protocol performance.

## Tools

The following tools are used in this project:

- **NS-3**: The core network simulator used for the project.
- **C++**: Used to write the simulation scripts.
- **Python**: Used to plot the results.

  > Note: NS-3 supports both Python and C++, so either language can be used depending on preference to write the simulation scripts.

## Installation

To get started with this project, follow these installation steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/ojaswichopra/ns3-simulation-routing_protocols.git
    cd ns3-simulation-routing_protocols
    ```

2. **Install Dependencies**: NS-3 has various optional extensions, but the main features just require a C++ compiler (g++ or clang++), Python (version 3.8 or above), CMake and a build-system (e.g. make, ninja, Xcode). 

3. **Install NS-3**: Follow the official [NS-3 Installation Guide](https://www.nsnam.org/wiki/Installation) to set up NS-3 on your machine.

4. **Run the Simulation**: After installing dependencies and building NS-3, you copy the simulation code into the scratch directory after changing back into the top level directory of NS-3.
   
   Build the script
   ```bash
    # Build the Script
    ./ns3 build
    ```
   Run the simulation, here you can change the protocol between OLSR, DSDV and AODV. You can also switch topology to mesh or star. Give path to the csv file where you want the performance parameters to be saved.
   ```bash
    # Run the Simulation
    ./ns3 run scratch/routing --protocol=DSDV --topology=mesh --outputFile=results.csv
    ```
   To see animation of the simulation, you can use NetAnim, which is a network animation tool used in conjunction with the NS-3 framework.
   ```bash
    # Change to NetAnim Directory
    cd netanim-3.109
    ./NetAnim
    ```
   You can now choose the XML file which was generated on running the simulation and see its animation within the NetAniim window.
   
## Usage

1. **Define Network Topology**: Edit the script to define the desired network topology (nodes, links, etc.).
2. **Choose Routing Algorithm**: Specify the routing algorithm to use in the simulation.
3. **Run the Simulation**: Execute the simulation using NS-3.
4. **Analyze Results**: Check the output for performance metrics like throughput, and packet delivery.

## Features

- Simulate network topologies with multiple nodes.
- Analyze performance of different routing algorithms.
- Support for both Python and C++.
- Generate reports on network performance metrics.
- Visualize the network using built-in NS-3 tools.

## Performance Metrics

After running the simulation, an csv file is generated with the following performance parameters.
1. **Throughput**: It measures how well the network can constantly provide data to the destination. It is derived in Mbps. For achieving better performance it should be high.
2. **Packet Delivery Ratio**: The ratio of the number of data packets delivered to the destination nodes and the number of data packets sent by source nodes. The performance would be better when it is high.
3. **End to end delay**: The average time interval between the generation of packets in a source node and successfully delivery of it in a destination node. The performance would be better when it is low.
4. **Number of Packets dropped**: The number of data packets that is not successfully delivered to the destination during transmission.
5. **Jitter**: It describes standard deviation of packet delay between all nodes.

## Contributers
- [Ojaswi Chopra](https://github.com/ojaswichopra)
- [Shubham Sharma](https://github.com/shukabum)
- [Shubhajit Biswas](https://github.com/Subhajit009iitr)
