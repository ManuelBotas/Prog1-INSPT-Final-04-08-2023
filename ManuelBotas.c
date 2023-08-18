#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

typedef struct 
{
    int cod_socio;
    char nom_ape[20];
    int categoria;
    char estado;
    float deuda;
}registro;

void Tecla();
void leerArchivo(FILE*, registro*);
float* SaldoACobrar(registro*, float*);
void Mostrar(float*, int);
void Informe(registro*, float*);
void mostrar_info_socio(registro*);

int main()
{
    FILE* f;
    char nombre[20] = "Deudores.txt";
    registro registros[50];
    float saldo_categoria[3] = {0};
    float mayor = 0;

    f = fopen(nombre, "r");
    if(f == NULL)
    {
        printf("Error al abrir el archivo");
        exit(1);
    }

    leerArchivo(f, registros);
    for (int i = 0; i < 50; i++)
    {
        if(registros[i].estado == 'A')
        {
            mostrar_info_socio(&registros[i]);
        }
    }

    Tecla();
    printf("\n\n");

    printf("Categor%ca \t Deuda total\n", 161);
    Mostrar(SaldoACobrar(registros, saldo_categoria), 0);

    printf("\n");
    Tecla();
    printf("\n\n");
    
    Informe(registros, &mayor);
    for (int i = 0; i < 50; i++)
    {
        if(registros[i].deuda == mayor)
        {
            mostrar_info_socio(&registros[i]);
        }
    }

    Tecla();
    fclose(f);
    
    return 0;
}

void Tecla()
{
    printf("Presione una tecla para continuar...");
    getch();
}

void leerArchivo(FILE* f, registro* reg)
{
    int i = 0;
    while(!feof(f))
    {
        fscanf(f, "%d %s %d %c %f", &reg[i].cod_socio, reg[i].nom_ape, &reg[i].categoria, &reg[i].estado, &reg[i].deuda);
        i++;
    }
}

float* SaldoACobrar(registro* reg, float* saldo)
{
    for (int i = 0; i < 50; i++)
    {
        switch(reg[i].categoria)
        {
            case 1:
                saldo[0] += reg[i].deuda;
                break;
            case 2:
                saldo[1] += reg[i].deuda;
                break;
            case 3:
                saldo[2] += reg[i].deuda;
                break;
        }
    }
    return saldo;
}

void Mostrar(float* saldo, int i)
{
    if(i == 3)
    {
        return;
    }
    else
    {
        printf("%8d \t %.2f\n", i+1, saldo[i]);
        Mostrar(saldo, i+1);
    }
}

void Informe(registro* reg, float* max)
{
    for (int i = 0; i < 50; i++)
    {
        if(reg[i].deuda > *max)
        {
            *max = reg[i].deuda;
        }
    }
}

void mostrar_info_socio(registro* reg)
{
    printf("%3cCodigo de socio: %20d\n", 32, reg->cod_socio);
    printf("%cNombre y apellido: %20s\n", 32, reg->nom_ape);
    printf("%9cCategoria: %20d\n", 32, reg->categoria);
    printf("%12cEstado: %20c\n", 32, reg->estado);
    printf("%13cDeuda: %20.2f\n", 32, reg->deuda);
    printf("\n");
}