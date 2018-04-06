#!usr/bin/env/python3.5
import random
import time

MUTATION = .2
POPSIZE = 30
MAXTRIES = 10
BOARD = 8

class individual:
    def __init__(self, size):
        self.gene = makeIndividual(size)
        self.fitness = (makeFitness(self.gene))


def makeIndividual(size):
    return [random.randint(0, BOARD - 1) for _ in range(size)]


def mate(x, y):
    split = random.randint(0, BOARD - 1)
    return x.gene[:split] + y.gene[split:]


def mutate(x):
    x.gene[random.randint(0, BOARD - 1)] = random.randint(0, BOARD - 1)


def makeFitness(x):
    ret = 0
    ldiag = []
    rdiag = []
    row = []
    for _ in range((BOARD * 2) - 1):
        rdiag.append(False)
        ldiag.append(False)
        row.append(False)
    for j in range(BOARD):
        i = x[j]
        if (row[i]):
            ret += 1
        else:
            row[i] = True
        if (rdiag[(BOARD - 1) - i + j]):
            ret += 1
        else:
            rdiag[(BOARD - 1) - i + j] = True
        if (ldiag[i + j]):
            ret += 1
        else:
            ldiag[i + j] = True
    return ret


def printBoard(x):
    for i in range(BOARD):
        for j in range(BOARD):
            if (x[j] == i):
                print('1', end=' ')
            else:
                print('0', end=' ')
        print()


def getParent(population):
    tries = 0
    while (True):
        cutoff = random.randint(0, BOARD-1)
        while (tries < MAXTRIES):
            index = random.randint(0, len(population) - 1)
            if (population[index].fitness < cutoff):
                return population[index]
            else:
                tries += 1
        tries = 0


def finished(population):
    for x in range(len(population)):
        if (population[x].fitness == 0):
            printBoard(population[x].gene)
            return True
    return False


def newGeneration(population):
    nextGen = []
    for _ in range(len(population)):
        mom = getParent(population)
        dad = getParent(population)
        newGenes = mate(mom, dad)
        child = individual(BOARD)
        child.gene = newGenes
        child.fitness = makeFitness(child.gene)
        if (random.random() < MUTATION):
            mutate(child)
        nextGen.append(child)
    return nextGen


def main():
    random.seed(time.time())
    done = False
    myPop = []
    for _ in range(POPSIZE):
        myPop.append(individual(BOARD))

    while (not done):
        done = finished(myPop)
        newPop = newGeneration(myPop)
        myPop = newPop


if (__name__ == "__main__"):
    main()
