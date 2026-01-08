from cs50 import get_float

change = 0

while True:
    change = get_float("Change: ") * 100
    if change > 0:
        break

available = [25, 10, 5, 1]

coins = 0

for coin in available:
    times = int(change/coin)
    coins += times
    change -= (coin * times)
    if (change == 0):
        break

print(coins)
