import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

from math import log

def main():
    print('Seleccione la cantidad de testeos realizados para cargar el plot')
    print('\ti.e. 13 abre resultsE5_13.dt')
    num = input('\t')
    mResultsFilename = "./results/resultsE6M_" + num + ".dt"
    qResultsFilename = "./results/resultsE6Q_" + num + ".dt"
    rResultsFilename = "./results/resultsE6R_" + num + ".dt"

    xFooLog1 = []
    xFooLog2 = []
    xFooLogR = []
    mResults = []
    qResults = []
    rResults = []

    inputFile = open(mResultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        xFooLog1.append(times[0])
        mResults.append(times[1])
    inputFile.close()

    inputFile = open(qResultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        xFooLog2.append(times[0])
        qResults.append(times[1])
    inputFile.close()

    inputFile = open(rResultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        xFooLogR.append(times[0])
        rResults.append(times[1])
    inputFile.close()

    Y1 = [(1 + log(x)) for x in xFooLog1]
    Y2 = [(1 + log(x)) for x in xFooLog2]
    Y3 = [(1 + log(x)) for x in xFooLogR]
    Y4 = [(x * log(x)) for x in xFooLogR]
    Y5 = [(x * log(x, 2)) for x in xFooLogR]

    #1
    plt.figure(0)
    xTicks = list(range(0, len(xFooLog1)))
    xTicksLbl = list(map(str, map(int, xFooLog1)))
    plt.xticks(xTicks, xTicksLbl)

    redPatch = mpatches.Patch(color = 'red', label = 'f(n) = 1 + ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Max Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('1 + ln(n) vs Max Averages')
    plt.plot(xTicks, Y1, 'tab:red', xTicks, mResults, 'tab:green')

    #2
    plt.figure(1)
    xTicks = list(range(0, len(xFooLog2)))
    xTicksLbl = list(map(str, map(int, xFooLog2)))
    plt.xticks(xTicks, xTicksLbl)
    plt.gcf().axes[0].yaxis.get_major_formatter().set_scientific(False)

    redPatch = mpatches.Patch(color = 'red', label = 'f(n) = 1 + ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('1 + ln(n) vs Quicksort Averages')
    plt.plot(xTicks, Y2, 'tab:red', xTicks, qResults, 'tab:green')

    #3
    plt.figure(2)
    xTicks = list(range(0, len(xFooLogR)))
    xTicksLbl = list(map(str, map(int, xFooLogR)))
    plt.xticks(xTicks, xTicksLbl)
    plt.gcf().axes[0].yaxis.get_major_formatter().set_scientific(False)

    redPatch = mpatches.Patch(color = 'red', label = 'f(n) = 1 + ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('1 + ln(n) vs Quicksort Averages')
    plt.plot(xTicks, Y3, 'tab:red', xTicks, rResults, 'tab:green')

    #4
    plt.figure(3)
    xTicks = list(range(0, len(xFooLogR)))
    xTicksLbl = list(map(str, map(int, xFooLogR)))
    plt.xticks(xTicks, xTicksLbl)
    plt.gcf().axes[0].yaxis.get_major_formatter().set_scientific(False)

    redPatch = mpatches.Patch(color = 'red', label = 'f(n) = n * ln(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('n * ln(n) vs Quicksort Averages')
    plt.plot(xTicks, Y4, 'tab:red', xTicks, rResults, 'tab:green')

    #5
    plt.figure(4)
    xTicks = list(range(0, len(xFooLogR)))
    xTicksLbl = list(map(str, map(int, xFooLogR)))
    plt.xticks(xTicks, xTicksLbl)
    plt.gcf().axes[0].yaxis.get_major_formatter().set_scientific(False)

    redPatch = mpatches.Patch(color = 'red', label = 'f(n) = n * log_2(n)')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort Averages')
    plt.legend(handles = [redPatch, greenPatch])
    plt.xlabel('n')
    plt.ylabel('times')

    plt.suptitle('n * log_2(n) vs Quicksort Averages')
    plt.plot(xTicks, Y5, 'tab:red', xTicks, rResults, 'tab:green')

    plt.show()

if __name__ == '__main__':
    main()
