### About the Simulation

Steps to at each time-step:

```
1. Determine Forces
2. Accumulate Forces
3. Calculate Acceleration (or lowest force)
4. Run Numerical Integrator
5. State Is Now Updated
6. Continue

```

How to Build:

```
cmake -S . -B build
```

```
cmake --build build/
```


How to Test
```
ctest --test-dir build --output-on-failure
```


How to reset cache
```
File → Invalidate Caches... → Invalidate and Restart
```