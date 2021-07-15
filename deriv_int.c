#include<stdio.h>
#include<stdlib.h>
#include<math.h>

// Funcao que gera uma distribuicao normal
float * normal_dist(int n, float step, float mean, float std){
    // numero de termos: n / step 
    // media: mean
    // desvio padrao: std
    int i;
    float *nvec;
    nvec = malloc((n/step) * sizeof(float)); 
    for(i = 0; i < n/step ; i++){
        nvec[i] = exp(-0.5*pow((i*step - mean)/std, 2))/(std*sqrt(2*M_PI));
    }
    return nvec;
}

int main(int argc, char* argv[]){
    // Declarando variaveis importantes
    int i,t_max = 5;
    float *t, *y,*yd_ref, *yi_ref, *yd, *z, *zd, *zi,*noise,  step = 0.01, offset = 0;

    // Abrindo arquivo de texto para escrita
    FILE* fdata = fopen("data.txt","w");
    
    // Recebendo argumentos pela linha de comando
    if(argc > 1){
        t_max = atoi(argv[1]);
        step = atof(argv[2]);
        offset = atof(argv[3]);
    }
    
    // Alocando memoria para as variaveis
    t = malloc((t_max/step) * sizeof(float));
    y = malloc((t_max/step) * sizeof(float));
    yd_ref = malloc((t_max/step) * sizeof(float));
    yi_ref = malloc((t_max/step) * sizeof(float));
    yd = malloc((t_max/step) * sizeof(float));
    z = malloc((t_max/step) * sizeof(float));
    zd = malloc((t_max/step) * sizeof(float));
    zi = malloc((t_max/step) * sizeof(float));

    // Vetor com distribuicao normal de media 0 e desvio padrão 0.2
    noise = normal_dist(t_max, step, 0, 0.2);
    
    //Valores iniciais para y, sua derivada e sua integral 
    y[0] = 0;
    zd[0] = 0;
    zi[0] = 0;
    
    // loop principal pelos instantes de tempo
    for(i = 1; i < t_max/step; i++){
        //t: vetor com os instantes de tempo
        t[i] = i*step - offset;

        //y: y(t) = t^2
        y[i] = pow(t[i],2);

        //yd_ref: derivada teorica de y
        yd_ref[i] = 2*t[i];
        
        //yi_ref: integral teorica de y
        yi_ref[i] = pow(t[i],3)/3;

        //yd: derivada numerica de y (Metodo de Euler)
        yd[i] = (y[i] - y[i-1])/step;

        //z: z(t) = y(t) + ruido branco gaussiano
        z[i] = y[i] + noise[rand()% (int) (t_max/step)]; // amostra aleatoria da distr. normal
        
        //zd: derivada numerica de y com ruido (Metodo de Euler)
        zd[i] = (z[i] - z[i-1])/step;

        //zd: derivada numerica de y com ruido (Metodo de Euler)
        zi[i] = zi[i-1] + z[i]*step;

        // Gravando os dados no arquivo de texto
        fprintf(fdata, "%f %f %f %f %f %f %f %f\n", t[i], y[i], yd[i], yd_ref[i], yi_ref[i], z[i], zd[i], zi[i]);
    }

    // fechando arquivo de texto
    fclose(fdata);

    // desalocando as variáveis
    free(t);
    free(y);
    free(yd_ref);
    free(yi_ref);
    free(yd);
    free(z);
    free(zd);
    free(zi);
    free(noise);

    return 0;
}
