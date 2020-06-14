import matplotlib.patches as mpatches
import matplotlib.pyplot as plt

def main():
    print('Seleccione la cantidad de testeos realizados para cargar el plot')
    print('\ti.e. 400 abre resultsE5_400.dt')
    resultsFilename = "./results/resultsE5_" + input('\t') + ".dt"

    msResults = []
    qsResults = []

    fNumTests = 0
    inputFile = open(resultsFilename, 'r')
    for line in inputFile:
        times = list(map(float, line.split()))
        msResults.append(times[0])
        qsResults.append(times[1])
        fNumTests = fNumTests + 1

    start = 1000
    stop  = fNumTests * 1000
    step  = 1000
    stop  = stop + step
    X = list(range(start, stop, step))

    plt.plot(X, msResults, 'tab:red', X, qsResults, 'tab:green')
    plt.xlabel('n')
    plt.ylabel('ms')

    redPatch = mpatches.Patch(color = 'red'  , label = 'Merge Sort')
    greenPatch = mpatches.Patch(color = 'green', label = 'Quicksort')
    plt.legend(handles = [redPatch, greenPatch])

    plt.suptitle('Merge Sort vs Quicksort (en milisegundos)')
    plt.show()

if __name__ == '__main__':
    main()
