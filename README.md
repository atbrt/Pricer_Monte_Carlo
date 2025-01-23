# Pricer_Monte_Carlo

## Project Overview
This project is a C++ implementation of a financial options pricer. The main objectives are:

- **Options pricing**:
  - Using the Black-Scholes formula for European Options
  - Using Monte-Carlo simulations
- **Replication strategy**:
  - Create a replication strategy with a portfolio of the underlying asset and a risk-free bond
- **Object-oriented programming**:
  - Create an object-oriented architecture for the code, which enables to add easily different types of options

## Requirements
- **Libraries:**
  - `<Eigen>` : I used this library for the pricing of American Options, to handle early-exercises of the option when pricing it (Longstaff-Schwarz method)
