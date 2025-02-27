# GameOfLifeSeedFinder

GameOfLifeSeedFinder is a utility designed to efficiently discover long-living initial configurations (seeds) in Conway's Game of Life. By exploring various initial states, this tool aims to identify patterns that persist over extended generations, providing insights into the game's complex behaviors.

## Overview

Conway's Game of Life is a cellular automaton where cells on a grid live, die, or evolve based on simple rules. Despite its straightforward mechanics, it exhibits complex and often unpredictable patterns. GameOfLifeSeedFinder automates the search for initial configurations that result in prolonged activity, aiding enthusiasts and researchers in studying these phenomena.

## Features

- **Automated Search**: Systematically explores a vast space of initial configurations to identify long-lasting patterns.
- **Efficiency**: Optimized algorithms ensure rapid evaluation of potential seeds.
- **Customization**: Users can define parameters such as grid size, population density, and evaluation criteria.
- **Output**: Generates detailed reports of discovered seeds, including their lifespan and evolutionary characteristics.

### Additional Features:
1. **Multithreaded Search Algorithm**:  
   - The program utilizes multiple threads to speed up the search for viable seed patterns in Conway's Game of Life.  
   - Each thread independently tests different initial configurations to find long-living patterns.  
   - Uses `std::async` and `std::atomic` to handle concurrency efficiently.

2. **Pattern Evaluation and Storage**:  
   - The algorithm evaluates each generated pattern based on how long it survives in the simulation.  
   - If a pattern lasts for at least `rounds - good_combination_threshold` generations, it is considered "good" and saved.  
   - Found patterns are stored in the `good_combinations/` directory, with each seed written to a unique file.

3. **Dynamic Grid and Customization**:  
   - Users can specify the grid size (`rows x cols`), the minimum lifespan required for a pattern, and the number of threads to use.  
   - The program adapts to different field sizes and seed densities.

4. **Game of Life Simulation with State Tracking**:  
   - The `Matrix` class manages the grid and tracks cell states over generations.  
   - Uses a **torus topology** (wrap-around edges) to simulate an infinite grid.  
   - Stores previous states to detect repeating cycles and stop early if necessary.

5. **Efficient Cell Processing**:  
   - Implements optimized neighbor counting and state updates for performance.  
   - Tracks changes in cell states to avoid unnecessary calculations.

## Installation

1. **Clone the Repository**:

   ```bash
   git clone https://github.com/dmitrii-gbe/GameOfLifeSeedFinder.git
   ```


2. **Navigate to the Project Directory**:

   ```bash
   cd GameOfLifeSeedFinder
   ```


3. **Build the Project**:

   ```bash
   make test_combinations
   ```


   Ensure you have a C++ compiler and `make` utility installed on your system.

## Usage

After building the project, run the executable with the desired parameters:


```bash
Binaries/test_combinations
```
You will be asked for providing desired threads count to be used by algorithm, game field size, and minimum generations count the field should live for. A possible input: 12 threads, 25 * 80 field size, and 3000 generations. **Field is considered as alive while it's life cycle accounts for more than 120 unique states**


## Contributing

Contributions are welcome! Feel free to fork the repository, make improvements, and submit pull requests. Please ensure that your contributions align with the project's objectives and maintain code quality.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

*Note: This project is a personal endeavor and is not affiliated with any official Game of Life organizations.* 
