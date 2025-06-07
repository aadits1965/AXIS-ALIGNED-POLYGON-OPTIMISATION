# AXION PRIME ZONING OPTIMIZER

## 🚀 Overview

In the futuristic city of **Axion Prime**, my mission is to redesign regulated zones by enclosing **at least K buildings** using a **simple, axis-aligned polygon**. Each building has an associated cost (positive or negative), and the goal is to **minimize total cost**, defined as:

```
Total Cost = Perimeter of the Polygon + Sum of weights of enclosed buildings
```

This C++ program evaluates multiple polygon construction strategies to find the configuration that achieves the **lowest cost** while respecting all constraints.

---

## 📥 Input Format

- First line: two integers `N` and `K` — total number of buildings and the minimum number to enclose.
- Next `N` lines: three integers `xᵢ yᵢ wᵢ` — coordinates and weight (cost) of the i-th building.

## 🧾 Output Format

- First line: a floating-point number — minimum total cost with **at least six digits** of precision.
- Subsequent lines: each describes a polygon edge with four real numbers: `x1 y1 x2 y2`, representing an **axis-aligned edge** from point (x1, y1) to (x2, y2), forming a **simple, closed polygon**.

---

## 🧠 Code Structure

- `struct node`: Represents a building with coordinates and cost.
- `_input()`: Reads and separates buildings into high-reward (`crystal`) and high-penalty (`mine`) sets.
- `generate_stripperX()` / `generate_stripperY()`: Construct horizontal/vertical strips optimized for enclosing valuable buildings.
- `generatebestcrystals()`: Greedily selects the highest-weight buildings to enclose and builds a custom polygon.
- `generateworstmines()`: Avoids enclosing high-penalty buildings by removing their influence from the cost.
- `main()`: Runs all strategies across 10 input cases and writes results to `output/outputXX.txt`.

---

## 📊 Output Example
```
12345.678901
0.0 0.0 0.0 5000.0
0.0 5000.0 5000.0 5000.0
5000.0 5000.0 5000.0 0.0
5000.0 0.0 0.0 0.0
```

---

## 🧪 Features

- ✅ Handles negative weights and non-uniform building distributions.
- ✅ Generates floating-point vertices for fine-grained polygon control.
- ✅ Produces axis-aligned, simple polygons with no self-intersections.
- ✅ Efficient on large datasets (up to 10,000 buildings).

---

## 📌 Notes

- Ensure that your input coordinates stay within [0, 10000].
- The polygon always adheres to **axis-aligned** and **simple** constraints.
- Floating-point precision is used to avoid overlapping and ensure valid geometry.
