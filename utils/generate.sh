echo "Generating 100..."
./gen.out random 100 500 1 1000 > 100.500.txt
./gen.out shuffle 100 2500 1 1000 > 100.2500.txt

echo "Generating 500..."
./gen.out random 500 5000 1 1000 > 500.5000.txt
./gen.out shuffle 500 75000 1 1000 > 500.7500.txt

echo "Generating 1000..."
./gen.out random 1000 10000 1 1000 > 1000.10000.txt
./gen.out shuffle 1000 250000 1 1000 > 1000.250000.txt

echo "Generating 5000..."
./gen.out random 5000 50000 1 1000 > 5000.50000.txt
./gen.out shuffle 5000 5000000 1 1000 > 1000.5000000.txt

echo "Generating 10000..."
./gen.out random 10000 100000 1 1000 > 10000.100000.txt
./gen.out shuffle 10000 15000000 1 1000 > 10000.15000000.txt
./gen.out shuffle 10000 45000000 1 1000 > 10000.45000000.txt

echo "Generating 15000..."
./gen.out random 15000 70000 1 1000 > 15000.70000.txt
./gen.out random 15000 150000 1 1000 > 15000.150000.txt
./gen.out shuffle 15000 15000000 1 1000 > 15000.15000000.txt
./gen.out shuffle 15000 30000000 1 1000 > 15000.30000000.txt
./gen.out shuffle 15000 45000000 1 1000 > 15000.45000000.txt
./gen.out shuffle 15000 60000000 1 1000 > 15000.60000000.txt

