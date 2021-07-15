import matplotlib.pyplot as plt

t = []
y = []
yd = []
yd_ref = []
yi_ref = []
z = []
zd = []
zi = []

# Abertura do arquivo com os dados
with open('data.txt','r') as f:
    # Leitura linha a linha do arquivo
    for line in f.readlines():
        values = line[:-1].split() # separacao das colunas
        # guardando os valores nas listas
        t.append(float(values[0]))
        y.append(float(values[1]))
        yd.append(float(values[2]))
        yd_ref.append(float(values[3]))
        yi_ref.append(float(values[4]))
        z.append(float(values[5]))
        zd.append(float(values[6]))
        zi.append(float(values[7]))

# Criacao dos graficos
fig, axs = plt.subplots(1, 2, figsize=(14,4))
fig.suptitle('Derivada sem ruído')
axs[0].plot(t, y)
axs[0].set(xlabel='t(s)', ylabel='Função y = x^2')
axs[0].grid()
axs[1].plot(t,yd, label='Numerica')
axs[1].set(xlabel='t(s)', ylabel='Derivada de y(t)')
axs[1].plot(t,yd_ref, label='Teorica')
axs[1].grid()
axs[1].legend()

fig, axs = plt.subplots(figsize=(10,5))
fig.suptitle('Adicao de ruído')
axs.plot(t, y, label='y(t) = x^2',zorder=2)
axs.set(xlabel='t(s)', ylabel='Função y(t) e z(t)')
axs.plot(t,z, label='z(t) = y(t) + ruido',zorder=1)
axs.grid()
axs.legend()

fig, axs = plt.subplots(1, 2, figsize=(14,4))
fig.suptitle('Derivada com ruído')
axs[0].plot(t, z)
axs[0].set(xlabel='t(s)', ylabel='Função z = x^2 + ruído')
axs[0].grid()
axs[1].plot(t,zd, label='Numerica com ruído (dz/dt Metodo de Euler)')
axs[1].set(xlabel='t(s)', ylabel='Derivada')
axs[1].plot(t,yd_ref, label='Teorica sem ruído (dy/dt)')
axs[1].grid()
axs[1].legend()

fig, axs = plt.subplots(1,2, figsize=(14,4))
fig.suptitle('Integral com ruído')
axs[0].plot(t, z)
axs[0].set(xlabel='t(s)', ylabel='Função z = x^2 + ruído')
axs[0].grid()
axs[1].plot(t,zi, label='Integral Numerica com ruído (Metodo de Euler)')
axs[1].set(xlabel='t(s)', ylabel='Integral')
axs[1].plot(t,yi_ref, label='Integral Teorica sem ruído')
axs[1].grid()
axs[1].legend()

plt.show()
