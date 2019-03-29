#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE  1
#define FALSE 0

//-------------------DATOS VEHICULO---------------------------------------------
struct datos{
       char modelo[20];
       char version[15];
       char color[15];
       float precio;
       };

typedef struct datos vehiculo;

struct nodo{
	vehiculo elemento;
	struct nodo *sig;
	struct nodo *ant;
};
//--------------------ESTRUCTURA MANEJO DE PILA---------------------------------
typedef struct {
	struct nodo *cima; //cima==final
	struct nodo *inicio;
	int nElem;
	int estado; //0 desbloqueada - 1 bloqueada
}Pila;

//-------------------FUNCIONES PARA PILA----------------------------------------
int estado(Pila mipila);
int lockPila(Pila mipila);
int tamanio(Pila *mipila);
int pila_vacia(Pila *mipila);
Pila* crear();
//---------------------ACCESO A LA LISTA----------------------------------------
vehiculo frente (Pila mipila);
vehiculo final (Pila mipila);
//---------------------------INSERCION------------------------------------------
void insertar_vacia(Pila *mipila, vehiculo ele);
void insertar_inicio(Pila *mipila, vehiculo ele);
void insertar_final(Pila *mipila, vehiculo ele);
void insertar_antes(Pila *mipila, vehiculo ele, int posicion);
void insertar_despues(Pila *mipila, vehiculo ele, int posicion);
void insertar_recuperacion(Pila *mipila, vehiculo ele);
//--------------------ELIMINACION-----------------------------------------------
void quitar_inicio(Pila *mipila);
void quitar_final(Pila *mipila);
void quitar_nodo(Pila *mipila, int posicion);
void full_pop(Pila *mipila);
//------------------------FUNCIONES ESPECIALES----------------------------------
void pop(Pila *mipila);
int posicion(Pila *mipila);
//-------------------------FUNCION PARA MOSTRAR---------------------------------
void imprimir(Pila *mipila);
//-------------------------FUNCIONES MANEJO DE ARCHIVOS-------------------------
void guardar(Pila *mipila);
void recuperar(Pila** mipila);
int ver_arch();
//-------------------VERIFICAR EXISTENCIA DE RESPALDO INVENTARIO----------------
int ver_arch(){
	FILE *F;
	F=fopen("INVENTARIO", "rb");
	if (F==NULL)
	return -1;
	else
	fclose(F);
	return 1;
}
//---------------------VERIFICAR TAMAÑO DE LA PILA------------------------------
int tamanio(Pila *mipila){
	return mipila->nElem;
}
//--------------------------FUNCIONES PILA BLOQUEADA----------------------------
int estado(Pila mipila) //Estado de la cola
{
    return mipila.estado;
}

int lockPila(Pila mipila) // Verificando estado de la cola
{
    if ( estado( mipila ) == 0 )
        return(TRUE);
    else
        return (FALSE);
}
//-------------------------GUARDAR DATOS EN ARCHIVO-----------------------------
void guardar(Pila *mipila){
	FILE *F;
	struct nodo *P;
	vehiculo a;
	P=mipila->inicio;

	F=fopen("INVENTARIO", "wb+");
	while(P!=NULL)
	{
		a=P->elemento;
		fwrite(&a,sizeof(a),1,F);
		P=P->sig;
		}
		fclose(F);
		printf("\n\n\tInventario guardado\n\n");
}
//---------------------RECUPERAR DATOS DESDE ARCHIVO----------------------------
//------------------------------INVENTARIO--------------------------------------
void recuperar(Pila** mipila){

	FILE *F;
	Pila *car;
	vehiculo a;
	car=*mipila;


	F=fopen("INVENTARIO", "rb");

	if (F==NULL)
	{
		printf("\n\nAun no ha iniciado la produccion\n\n");
		system( "pause>nul" );
		exit (0);
		}

	fread(&a,sizeof(a),1,F);

	while(!feof(F))
	{
		insertar_recuperacion(car,a);
		fread(&a,sizeof(a),1,F);
		}

	printf("\n\n\tInventario recuperado\n\n");
}
//-----------------------OBTENER POSICION PARA BORRAR---------------------------
int posicion(Pila *mipila){
    struct nodo *aux;
	int pos=0;
	int x;

	if(!pila_vacia(mipila))
	{
       pos=1;
		char auxmod[20];
      aux=mipila->inicio;
       printf("\nQue auto desea eliminar\n");
       fflush(stdin);
       gets(auxmod);
       while(aux != NULL)
       {
       if((strcmp(auxmod,aux->elemento.modelo)!=0))
       {
       pos++;
        aux=aux->sig;
        }
        else
        {
            break;
            }
   }
   x=pos;
   if (x>mipila->nElem)
   x=-1;
   else
   printf("\n\nLa posicion del elemento seleccionado es %d", x);
   return x;
}
}
//-----------------------ACCESO ELEMENTOS LISTA---------------------------------
vehiculo frente(Pila mipila) //Pidiendo primer elemento
{
   return (mipila.inicio->elemento);
}

vehiculo final(Pila mipila) //Pidiendo ultimo elemento
{
   return (mipila.cima->elemento);
}
//-----------------------VERIFICANDO TAMANO DE PILA-----------------------------

int pila_vacia(Pila *mipila){
	if ( tamanio( mipila ) == 0 )
        return(TRUE);
    else
        return (FALSE);
}

//-------------------------INICICIALIZANDO PILA--------------------------------

Pila* crear( )
{
    Pila *aux;
    aux = (Pila *)malloc(sizeof(Pila));
    aux->nElem = 0;
    aux->estado=0;
    aux->cima = NULL;
    aux->inicio = NULL;
    return (aux);
}

//---------------------------FUNCIONES AÑADIR ELEMENTO--------------------------
//--------------------INSERCIÓN DE RECUPERACION---------------------------------
void insertar_recuperacion(Pila *mipila, vehiculo ele){
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------

    if( !pila_vacia( mipila ) )
    {
	a->sig=NULL;
    a->ant=mipila->cima;
    mipila->cima->sig=a;
    mipila->cima=a;
	}
	else
	{
     a->sig=a->ant=NULL;
     mipila->inicio=mipila->cima=a;
	}
    mipila->nElem++;
}
//-----------------------INSERCION LISTA VACIA----------------------------------
void insertar_vacia(Pila *mipila, vehiculo ele){
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------
    a->sig=a->ant=NULL;
    mipila->inicio=mipila->cima=a;
    mipila->nElem++;
}
//-------------------------INSERCION INICIO-------------------------------------
void insertar_inicio(Pila *mipila, vehiculo ele){
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------
	a->ant=NULL;
    a->sig=mipila->inicio;
    mipila->inicio->ant=a;
    mipila->inicio=a;
    mipila->nElem++;
}
//-------------------------INSERCION FINAL--------------------------------------
void insertar_final(Pila *mipila, vehiculo ele){
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------
    a->sig=NULL;
    a->ant=mipila->cima;
    mipila->cima->sig=a;
    mipila->cima=a;
    mipila->nElem++;
}
//-------------------------INSERCION ANTES--------------------------------------
void insertar_antes(Pila *mipila, vehiculo ele, int posicion){
	int i;
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a, *actual;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------
    actual = mipila->inicio;
    for(i=1;i<posicion;i++)
    actual=actual->sig;
    a->sig=actual;
    a->ant=actual->ant;
    if(actual->ant == NULL)
    mipila->inicio=a;
    else
    actual->ant->sig=a;
    actual->ant=a;
    mipila->nElem++;
}
//-------------------------INSERCION DESPUES------------------------------------
void insertar_despues(Pila *mipila, vehiculo ele, int posicion){
	int i;
	//-------------CREANDO NUEVO NODO-------------------------
      struct nodo *a, *actual;
    a = (struct nodo *)malloc( sizeof(struct nodo) );
    a->elemento = ele;
    a->sig = a->ant = NULL;
    //--------------------------------------------------------
    actual = mipila->inicio;
    for(i=1;i<posicion;i++)
    actual=actual->sig;
    a->sig=actual->sig;
    a->ant=actual;
    if(actual->sig == NULL)
    mipila->cima=a;
    else
    actual->sig->ant=a;
    actual->sig=a;
    mipila->nElem++;
}
//--------------------------FUNCIONES DE ELIMINACION----------------------------
//---------------------------------QUITAR INICIO--------------------------------
void quitar_inicio(Pila *mipila)
{
	struct nodo *a;
	a = mipila->inicio;
       mipila->inicio=mipila->inicio->sig;
       if(mipila->inicio == NULL)
       {
       mipila->cima=NULL;
       }
       else
       {
       mipila->inicio->ant = NULL;
       }
       free(a);
    mipila->nElem--;
}
//---------------------------------QUITAR FINAL---------------------------------
void quitar_final(Pila *mipila)
{
	struct nodo *a;
	a=mipila->cima;
	mipila->cima->ant->sig=NULL;
	mipila->cima=mipila->cima->ant;
	free(a);
    mipila->nElem--;
}
//---------------------------------QUITAR NODO----------------------------------
void quitar_nodo(Pila *mipila, int posicion)
{
	int i;
	struct nodo *a, *actual;
	actual=mipila->inicio;
	for(i=1;i<posicion;i++)
	 actual=actual->sig;
	a=actual;
	actual->ant->sig = actual->sig;
	actual->sig->ant=actual->ant;
	free(a);
    mipila->nElem--;
}

//-------------------------------VISUALIZAR PILA--------------------------------

void imprimir(Pila *mipila) //Imprimir elementos
{
	
     int cont=1; //Auxiliar de numeración
     int opc; //Auxiliar del Case
     struct nodo *aux;
     if( !pila_vacia( mipila )) //Verificando cola no vacía
     {
     printf("\n\n\t1. Todos\n");
     printf("\t2. Primer alumno registrado\n");
     printf("\t3. %cltimo alumno registrado\n", -23);
     /*printf("\t4. Orden inverso\n");*/
     fflush(stdin);
     scanf("%d", &opc);
     switch (opc)
     {
            case 1:
                 system( "cls" );
     aux=mipila->inicio;
     printf("\n\tAutos\n");
    while(aux!=NULL)
    {
        printf("\n\t%d. Modelo: %s Version: %s Color: %s Precio: %.2f\n",cont, aux->elemento.modelo,aux->elemento.version,aux->elemento.color,aux->elemento.precio);
        aux=aux->sig;
        cont++;
    }
    break;

    case 2:
         system( "cls" );
         vehiculo primer;
         primer=frente(*mipila);
         printf("\n\t* Modelo: %s Version: %s Color: %s Precio: %.2f\n", primer.modelo,primer.version,primer.color,primer.precio);
         break;

    case 3:
         system( "cls" );
         vehiculo ultimo;
         ultimo=final(*mipila);
         printf("\n\t* Modelo: %s Version: %s Color: %s Precio: %.2f\n",ultimo.modelo,ultimo.version,ultimo.color,ultimo.precio);
         break;

    /*case 4:
		system( "cls" );
		cont=mipila->nElem;
		aux=mipila->cima;
        while(aux!=NULL)
    {
        printf("\n\t%d. Modelo: %s Version: %s Color: %s Precio: %.2f\n",cont, aux->elemento.modelo,aux->elemento.version,aux->elemento.color,aux->elemento.precio);
        aux=aux->ant;
        cont--;
    }
    break;*/

    default: printf("\nOpci\242n inv\240lida\n");
}
}
else
printf("\nNo hay alumnos registrados\n");
}

//------------------------------ELIMINAR PILA-----------------------------------

void full_pop(Pila *mipila){
	struct nodo *aux, *reemplazo;
	if(!pila_vacia( mipila ))
	{
       aux = mipila->inicio;

        while( aux->sig != NULL )
        {
            reemplazo = aux->sig;
            free( aux );
            aux = reemplazo;
        }
        mipila->inicio = NULL;
        mipila->cima = NULL;
        mipila->nElem = 0;
        printf( "\nProduccion defectuosa, inventario eliminado!" );
    }
    else
        printf( "\nNo hay inventario\n" );

    return ;
}
