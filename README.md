# Network Simulation using NS-3

This project involves creating a simulation of a network topology to analyze the performance of various routing algorithms or network protocols. The simulation is built using NS-3, a discrete-event network simulator, and focuses on evaluating the efficiency and reliability of different routing techniques in networking.

## Table of Contents

- [Description](#description)
- [Skills](#skills)
- [Tools](#tools)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
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
    git clone https://github.com/ojaswichopra/network-simulation-ns3.git
    cd network-simulation-ns3
    ```

2. **Install NS-3**: Follow the official [NS-3 Installation Guide](https://www.nsnam.org/wiki/Installation) to set up NS-3 on your machine.

3. **Install Dependencies**:
    - **For Python**: 
      ```bash
      sudo apt-get install python3
      ```
    - **For C++**: Ensure that you have a C++ compiler installed.

4. **Run the Simulation**:
   After setting up NS-3 and installing dependencies, you can run the simulation with:
  

## Usage

1. **Define Network Topology**: Edit the script to define the desired network topology (nodes, links, etc.).
2. **Choose Routing Algorithm**: Specify the routing algorithm to use in the simulation.
3. **Run the Simulation**: Execute the simulation using NS-3.
4. **Analyze Results**: Check the output for performance metrics like throughput, latency, and packet delivery.

## Features

- Simulate network topologies with multiple nodes.
- Analyze performance of different routing algorithms.
- Support for both Python and C++.
- Generate reports on network performance metrics.
- Visualize the network using built-in NS-3 tools.

## Contributers
- [Ojaswi Chopra](https://github.com/ojaswichopra)
- [Shubham Sharma](https://github.com/shukabum)
- [Shubhajit Biswas](https://github.com/Subhajit009iitr)
