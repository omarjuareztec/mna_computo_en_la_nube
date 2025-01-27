// suma_arreglos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <cstdlib> 

#ifdef _OPENMP
    #include <omp.h>
    #define en_paralelo true
#else
    #define omp_get_thread_num() 0
    #define en_paralelo false
#endif


#define N 1000
#define chunk 100
#define mostrar 10
int numero_aleatorio;

void imprimeArreglo(float* d);


int main()
{
    if (en_paralelo)
    {
        std::cout << "Sumando arreglosa en paralelo!\n";
    }
    else
    {
        std::cout << "Sumando arreglos!\n";
    }

    // Se crean 3 arreglos, a y b para con números, y c para guardar la suma de a y b
    float a[N], b[N], c[N];
    int i;
    int tid;

    // Se llenan los arreglos, pueden ser números aleatorios
    // Inicializar la semilla aleatoria
    srand(time(0));
    for (i = 0; i < N; i++)
    {
        a[i] = i * 10;
        // Generar número entre 1 y 100
        numero_aleatorio = rand() % 100 + 1;
        b[i] = numero_aleatorio;
    }
    
    // Creando un for paralelo si esta presente la librería, de lo contrario se ejecuta secuencial
    int pedazos = chunk;

    #pragma omp parallel for \
    shared(a, b, c, pedazos) private(i) \
    schedule(static, pedazos)

    for (i = 0; i < N; i++)
    {
        c[i] = a[i] + b[i];

        //Lineas para imprimir el número del thread del for actual
        //tid = omp_get_thread_num();
        //std::cout << "El thread " << tid << " esta en marcha " << std::endl;
    }

    // Imprimiendo los arreglos
    std::cout << "Imprimendo los primeros " << mostrar << " valores del arreglo a: " << std::endl;
    imprimeArreglo(a);

    std::cout << "Imprimendo los primeros " << mostrar << " valores del arreglo b: " << std::endl;
    imprimeArreglo(b);

    std::cout << "Imprimendo los primeros " << mostrar << " valores del arreglo c: " << std::endl;
    imprimeArreglo(c);

}

// Función para imprimir arreglos
void imprimeArreglo(float* d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << ",\t";
    std::cout << std::endl;
}
