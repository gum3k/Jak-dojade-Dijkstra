# Jak-dojade-Dijkstra

**Jak-dojade-Dijkstra** is a C++ application that calculates the shortest path between public transportation stops (represented as vertices on a graph) using Dijkstra's algorithm. This tool is intended to be used with a grid-based map representing a transportation network, where each stop is connected by edges with weights (representing travel time or distance).

## Features
- Implements Dijkstra’s shortest path algorithm to find the fastest route between two points.
- The program supports a transportation network modeled as a grid with nodes and weighted edges.
- Handles queries to find the shortest path between multiple pairs of stops.

## Requirements
- A C++ compiler supporting C++11 or later.

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/gum3k/Jak-dojade-Dijkstra.git
   ```

2. Compile the program:
   ```bash
   g++ -o jakdojade main.cpp
   ```

3. Run the program:
   ```bash
   ./jakdojade
   ```

## Usage

After running the program, it will prompt you for inputs. You will need to:
- Provide the dimensions of the map (width and height).
- Input the details of flights between cities, including the source, destination, and time.
- Input queries specifying the source and destination for which the shortest path should be calculated.

The program will compute the shortest path based on the graph's edges and display the result.

### Example:
Input:
```
5 5
*****
*#*#*
#*#*#
*#*#*
*****
3
A B 5
B C 2
C D 4
2
A D 1
B D 2
```
Output:
```
10
```

## Code Structure

- **Vertex**: Represents a stop or node in the graph with coordinates `(x, y)` and a name.
- **Edge**: Represents a directed edge between two vertices with a weight.
- **List**: A simple linked list used to represent the adjacency list for the graph.
- **dijkstra()**: Implements Dijkstra's algorithm to calculate the shortest path between two stops.
