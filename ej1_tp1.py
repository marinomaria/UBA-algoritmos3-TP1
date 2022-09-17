import numpy as np

n = 3
m = 6

c1 = (2,1)
c2 = (2,4)
c3 = (0,4)


bottom = -1

grilla = np.full((n,m),bottom)

grilla[(0,0)] = 1
# grilla[(0,1)] = 2
grilla[c1] = int(n*m/4)
grilla[c2] = int(n*m/2)
grilla[c3] = int(3*n*m/4)
grilla[(0,1)] = n*m

cantidad_total_de_formas = 0
steps = 0
# ultimo_borde

def dibujo():
    print(np.flip(grilla,0))
    print()
dibujo()

# print(grilla[0,0])

def solver(x,y):
    global grilla
    global steps
    steps+=1
    global cantidad_total_de_formas
    dibujo()
    i = grilla[x,y]

    ##Siguiente target
    if i < grilla[c1]:
        siguiente_target = c1
    elif i < grilla[c2]:
        siguiente_target = c2
    elif i < grilla[c3]:
        siguiente_target = c3
    elif i < grilla[(0,1)]:
        siguiente_target = (0,1)
    ##Siguiente target

    ##Poda Manhattan
    if np.sum(np.abs(np.array((x,y))-np.array(siguiente_target))) > grilla[siguiente_target]-i:
        return
    ##Poda Manhattan


    ##Checkpoint
    if i == grilla[c1]-1:
        if np.sum(np.abs(np.array((x,y))-np.array(c1))) == 1:
            solver(c1[0],c1[1])
        else:
            return

    elif i == grilla[c2]-1:
        if np.sum(np.abs(np.array((x,y))-np.array(c2))) == 1:
            solver(c2[0],c2[1])
        else:
            return
    elif i == grilla[c3]-1:
        if np.sum(np.abs(np.array((x,y))-np.array(c3))) == 1:
            solver(c3[0],c3[1])
        else:
            return

    elif i == n*m-1:
        if (x,y) == (1,1) or (x,y) == (0,2):
            dibujo()
            print()
            print ('YAY\n'*3)
            cantidad_total_de_formas+=1
            return 
    ##Checkpoint
        
    else:
        ##Poda loops
        adyacentes, checkpoint_al_lado = adyacentes_posibles(x,y)
        if t_bone(x,y) and not checkpoint_al_lado:
            return
        ##Poda loops


    ##Poda Filler
         if len(adyacentes) == 3:
             if t_bone(el_de_adelante[0],el_de_adelante[1])
                 pinto_compatible()
             return adyacentes = adyacentes[0/2]
    ##Poda Filler

    ##Backtracking
        for pos in adyacentes:
            grilla[pos] = i+1
            solver(pos[0],pos[1])
            grilla[pos] = bottom
    ##Backtracking

def el_de_adelante(adyacentes):
    if len(adyacentes) == 3:
        if np.linalg.norm(np.array(adyacentes[0])-np.array(adyacentes[1]))==2:
            return adyacentes[2]
        elif np.linalg.norm(np.array(adyacentes[0])-np.array(adyacentes[2]))==2:
            return adyacentes[1]
        else:
            return adyacentes[0]

def posible_filler(x,y):
    pintado = -8
    adyacentes, checkpoint_al_lado = adyacentes_posibles(x,y)
    if len(adyacentes) == 2:
        if np.linalg.norm(np.array(adyacentes[0])-np.array(adyacentes[1]))==2:
            if not checkpoint_al_lado:
                pinto(adyancente[0])

# pinto((x,y)):
    # if (x,y) == adyacente[1]:
        # return True
    # grilla[(x,y)] = pintado
    # for pos in adyacentes_posibles(x,y)
        # pinto(pos)


def t_bone(x,y):
    adyacentes, checkpoint_al_lado = adyacentes_posibles(x,y)
    if len(adyacentes) == 2:
        if np.linalg.norm(np.array(adyacentes[0])-np.array(adyacentes[1]))==2:
            if not checkpoint_al_lado:
                return True
    return False


def adyacentes_posibles(x,y):
    global grilla
    posibles = []
    value = grilla[(x,y)]
    checkpoint_al_lado = False
    if x>0:
        if grilla[x-1,y] == bottom:
            posibles += [(x-1,y)]
        elif grilla[x-1,y] > value:
            checkpoint_al_lado = True
    if x<(n-1):
        if grilla[x+1,y] == bottom:
            posibles += [(x+1,y)]
        elif grilla[x+1,y] > value:
            checkpoint_al_lado = True
    if y>0:
        if grilla[x,y-1] == bottom:
            posibles += [(x,y-1)]
        elif grilla[x,y-1] > value:
            checkpoint_al_lado = True
    if y<(m-1):
        if grilla[x,y+1] == bottom:
            posibles += [(x,y+1)]
        elif grilla[x,y+1] > value:
            checkpoint_al_lado = True
    return posibles, checkpoint_al_lado

def paridad_compatible():
    for pos in [c1,c2,c3]:
        if (grilla[c1])%2 == np.sum(np.array(c1))%2:
            return False
    return True



if paridad_compatible():
    solver(0,0)
    print('formas totales: ',cantidad_total_de_formas)
    print('cantidad de pasos:', steps)
else:
    print('formas totales:',0)
    print('cantidad de pasos:', 1)


