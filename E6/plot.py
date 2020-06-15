import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

from math import log

def main():
    print('Seleccione la cantidad de testeos realizados para cargar el plot')
    print('\ti.e. 13 abre resultsE5_13.dt')
    num = input('\t')
    mResultsFilename = "./results/resultsE6M_" + num + ".dt"
    qResultsFilename = "./results/resultsE6Q_" + num + ".dt"

    xFooLogN = []
    mResults = []
    qResults = []

    inputFile = open(mResultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        xFooLogN.append(times[0])
        mResults.append(times[1])
    inputFile.close()

    inputFile = open(qResultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        qResults.append(times[1])
    inputFile.close()

    Y = [(log(x)) for x in xFooLogN]

    #1
    plt.figure(0)
    xTicks = list(range(0, len(xFooLogN)))
    xTicksLbl = list(map(str, map(int, xFooLogN)))
    plt.xticks(xTicks, xTicksLbl)

    redPatch = mpatches.Patch(color = 'red'  , label = 'f(n) = 1 + ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Max Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('1 + ln(n) vs Max Averages')
    plt.plot(xTicks, Y, 'tab:red', xTicks, mResults, 'tab:green')

    #2
    plt.figure(1)
    xTicks = list(range(0, len(xFooLogN)))
    xTicksLbl = list(map(str, map(int, xFooLogN)))
    plt.xticks(xTicks, xTicksLbl)
    plt.gcf().axes[0].yaxis.get_major_formatter().set_scientific(False)

    redPatch = mpatches.Patch(color = 'red'  , label = 'f(n) = 1 + ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('1 + ln(n) vs Quicksort Averages')
    plt.plot(xTicks, Y, 'tab:red', xTicks, qResults, 'tab:green')

    plt.show()

if __name__ == '__main__':
    main()
