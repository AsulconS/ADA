import bubbleSortTest
import insertSortTest

import matplotlib.pyplot as plt

from linearAlgebra import MatVector

if __name__ == '__main__':
    print('\nut: Unidades de Tiempo\n')
    (w01, w11, w21) = bubbleSortTest.bubbleSortTest()
    (w02, w12, w22) = insertSortTest.insertSortTest()

    xAxis = MatVector(list(range(0, 100000001, 100)))

    fig, axs = plt.subplots(3, 3)
    yAxis00 = (xAxis ** 2).addScalar(2)
    axs[0][0].plot(xAxis.data, yAxis00.data, 'tab:red')
    axs[0][0].set_title('Bubble Sort (Comparaciones)')

    yAxis01 = (xAxis ** 2).scale(4).addScalar(4)
    axs[0][1].plot(xAxis.data, yAxis01.data, 'tab:red')
    axs[0][1].set_title('Bubble Sort (Asignaciones)')

    yAxis02 = (xAxis ** 2).scale(w21) + xAxis.scale(w11).addScalar(w01)
    axs[0][2].plot(xAxis.data, yAxis02.data, 'tab:orange')
    axs[0][2].set_title('Crecimiento de los segundos con respecto al tiempo')

    yAxis10 = (xAxis ** 2) + xAxis.scale(2).addScalar(-2)
    axs[1][0].plot(xAxis.data, yAxis10.data, 'tab:green')
    axs[1][0].set_title('Insert Sort (Comparaciones)')

    yAxis11 = (xAxis ** 2) + xAxis.scale(3).addScalar(-2)
    axs[1][1].plot(xAxis.data, yAxis11.data, 'tab:green')
    axs[1][1].set_title('Insert Sort (Asignaciones)')

    yAxis12 = (xAxis ** 2).scale(w22) + xAxis.scale(w12).addScalar(w02)
    axs[1][2].plot(xAxis.data, yAxis12.data, 'tab:blue')
    axs[1][2].set_title('Crecimiento de los segundos con respecto al tiempo')

    axs[2][0].plot(xAxis.data, yAxis00.data, 'tab:red', xAxis.data, yAxis10.data, 'tab:green')
    axs[2][0].set_title('Bubble Sort vs Insert Sort (Comparaciones)')

    axs[2][1].plot(xAxis.data, yAxis01.data, 'tab:red', xAxis.data, yAxis11.data, 'tab:green')
    axs[2][1].set_title('Bubble Sort vs Insert Sort (Asignaciones)')

    axs[2][2].plot(xAxis.data, yAxis02.data, 'tab:orange', xAxis.data, yAxis12.data, 'tab:blue')
    axs[2][2].set_title('Crecimiento de los segundos con respecto al tiempo (VS)')

    i = 1
    for ax in axs.flat:
        if i % 3 == 0:
            ax.set(xlabel = 'ut', ylabel = 's')
        else:
            ax.set(xlabel = 'n', ylabel = 'ut')
        i = i + 1

    plt.show()
