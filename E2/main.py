import matplotlib.pyplot as plt

from math import log2

def main():
    X  = list(range(1, 1000))
    Y1 = list(range(1, 1000)) # Merge Sort
    Y2 = list(range(1, 1000)) # Insert Sort en peor caso
    Y3 = list(range(1, 1000)) # Insert Sort en mejor caso

    for i in range(len(X)):
        Y1[i] = X[i] * log2(X[i])
        Y2[i] = X[i] ** 2
        Y3[i] = X[i]

    _, (ax1, ax2, ax3, ax4) = plt.subplots(1, 4)

    ax1.plot(X, Y1, 'tab:orange')
    ax1.set_title('Merge Sort')

    ax2.plot(X, Y2, 'tab:blue')
    ax2.set_title('Insert Sort peor caso')

    ax3.plot(X, Y3, 'tab:green')
    ax3.set_title('Insert Sort mejor caso')

    ax1.set(xlabel = 'n', ylabel = 'ut')
    ax2.set(xlabel = 'n')
    ax3.set(xlabel = 'n')

    plt.suptitle('Ejercicio 1')
    plt.show()

if __name__ == '__main__':
    main()
