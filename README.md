# Flu Chess Engine

Flu is a high-performance chess engine designed to analyze and play chess at a strong level. It is built using C++ and features various advanced search techniques.

## Features
- Move generation and evaluation
- Minimax and alpha-beta pruning
- UCI (Universal Chess Interface) support
- Bitboard-based representation for fast computations
- Search optimizations such as quiescence search

## Compilation Instructions
To compile Flu into an executable:

### **Using Visual Studio**
1. Open **Visual Studio**.
2. Create a new **C++ Empty Project**.
3. Add all **.cpp and .h** files to the project.
4. Set the **entry point** (`main.cpp`) in **Source Files**.
5. Configure **C++ Include Directories** under Project Properties.
6. Click **Build > Build Solution** (or press `Ctrl + Shift + B`).
7. The EXE will be located in the **Debug** or **Release** folder.

### **Using g++ (MinGW) on Windows**
1. Open a terminal in the project directory.
2. Run the following command:
   ```sh
   g++ -std=c++17 -O2 -o flu *.cpp
   ```
3. Run Flu using:
   ```sh
   ./flu
   ```

### **Using g++ on Linux**
1. Install `g++` if not already installed:
   ```sh
   sudo apt install g++
   ```
2. Compile Flu:
   ```sh
   g++ -std=c++17 -O2 -o flu *.cpp
   ```
3. Run Flu:
   ```sh
   ./flu
   ```

## Usage
Flu supports the **UCI protocol**, meaning it can be used with GUI interfaces like **Arena, CuteChess, and ChessBase**.

To start Flu in UCI mode, run:
```sh
./flu
```
Then type `uci` to confirm UCI compatibility.

## Notes
- Flu does not currently support **NNUE** (Neural Network evaluation) but may in future updates.
- Ensure `hash` and `eval` files are correctly initialized for best performance.

## License
Flu is an open-source project. Feel free to modify and improve it!

