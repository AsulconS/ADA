import bubbleSortTest
import insertSortTest

import matplotlib.pyplot as plt

from linearAlgebra import MatVector

def times():
    mode = input('\nIngrese el modo de generacion del arreglo:\na: aleatorio\nc: creciente\nd: decreciente\n\n')

    (w01, w11) = bubbleSortTest.bubbleSortTest(mode)
    (w02, w12) = insertSortTest.insertSortTest(mode)

    xAxis = MatVector(list(range(0, 10 ** 18, 10 ** 12)))

    _, (ax1, ax2, ax3) = plt.subplots(1, 3)

    yAxis02 = xAxis.scale(w11).addScalar(w01)
    ax1.plot(xAxis.data, yAxis02.data, 'tab:orange')
    ax1.set_title('Bubble Sort')

    yAxis12 = xAxis.scale(w12).addScalar(w02)
    ax2.plot(xAxis.data, yAxis12.data, 'tab:blue')
    ax2.set_title('Insert Sort')

    ax3.plot(xAxis.data, yAxis02.data, 'tab:orange', xAxis.data, yAxis12.data, 'tab:blue')
    ax3.set_title('Bubble Sort vs Insert Sort')

    ax1.set(xlabel = 'ut', ylabel = 's')
    ax2.set(xlabel = 'ut')
    ax3.set(xlabel = 'ut')

    t = 'Crecimiento de los segundos con respecto al tiempo para: '
    if mode == 'a':
        t = t + 'Arreglo Aleatorio'
    elif mode == 'c':
        t = t + 'Arreglo Creciente'
    else:
        t = t + 'Arreglo Decreciente'

    plt.suptitle(t)
    plt.show()

def complexity():
    xAxis = MatVector(list(range(0, 100000001, 100)))

    _, axs = plt.subplots(3, 2)

    yAxis00 = (xAxis ** 2).addScalar(2)
    axs[0][0].plot(xAxis.data, yAxis00.data, 'tab:red')
    axs[0][0].set_title('Bubble Sort (Comparaciones)')

    yAxis01 = (xAxis ** 2).scale(4).addScalar(4)
    axs[0][1].plot(xAxis.data, yAxis01.data, 'tab:red')
    axs[0][1].set_title('Bubble Sort (Asignaciones)')

    yAxis10 = (xAxis ** 2) + xAxis.scale(2).addScalar(-2)
    axs[1][0].plot(xAxis.data, yAxis10.data, 'tab:green')
    axs[1][0].set_title('Insert Sort (Comparaciones)')

    yAxis11 = (xAxis ** 2) + xAxis.scale(3).addScalar(-2)
    axs[1][1].plot(xAxis.data, yAxis11.data, 'tab:green')
    axs[1][1].set_title('Insert Sort (Asignaciones)')

    axs[2][0].plot(xAxis.data, yAxis00.data, 'tab:red', xAxis.data, yAxis10.data, 'tab:green')
    axs[2][0].set_title('Bubble Sort vs Insert Sort (Comparaciones)')

    axs[2][1].plot(xAxis.data, yAxis01.data, 'tab:red', xAxis.data, yAxis11.data, 'tab:green')
    axs[2][1].set_title('Bubble Sort vs Insert Sort (Asignaciones)')

    for ax in axs.flat:
        ax.set(xlabel = 'n', ylabel = 'ut')
    for ax in axs.flat:
        ax.label_outer()

    plt.suptitle('Graficas de complejidad')
    plt.show()

def main():
    print('\nut: Unidades de Tiempo\n')
    action = bool(int(input('Ingrese los graficos que mostrara:\n0: graficas de complejidad\n1: analisis de tiempos\n\n')))
    if action:
        times()
    else:
        complexity()

if __name__ == '__main__':
    main()
