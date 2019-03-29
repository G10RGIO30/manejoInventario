#include "listadoble.h"

//----------------------------------MAIN ADMINASTRADOR--------------------------

int main(void)
{
	system("COLOR fc");
    Pila *car;
    char op; //Auxiliar del Case
    int opi; //Auxiliar de insercion (case)
    int ope; //Auxiliar de eliminacion (case)
    int pos; //Posición a insertar/borrar
    vehiculo x;
    car = crear( );
    if(ver_arch()==1)
    recuperar( &car );
    int autos=car->nElem;
    do
    {
        fflush( stdin );
        system( "cls" );
        printf( "\n\t\tMenu\n" );
        printf( "\n\t\tAutos ingresados: %d\n",autos);
        if ( lockPila(*car) )
        printf("\nEstado actual de la produccion: Activa\n\n");
        else
        printf("\n\nEstado actual de la produccion: Detenida\n\n");
        printf( "1.- Alta en el inventario\n" );
        printf( "2.- Baja en el inventario\n" );
        printf( "3.- Mostrar inventario\n" );
        if ( lockPila(*car) )
        printf( "4.- Detener produccion\n" );
        else
        printf( "4.- Poner produccion en marcha\n" );
        printf( "5.- Eliminar inventario\n" );
        printf( "6.- Salir\n" );

        printf( "\n\nEliga una opcion: " );
        scanf( "%c", &op );

        fflush( stdin );
        switch( op )
        {
             case '1':
					if ( lockPila(*car) )
                  {
                      system( "cls" );
                      printf( "Ingrese datos del auto: " );
                      printf("\nModelo:\n");
                      fflush(stdin);
                      gets(x.modelo);
                      printf("\nVersion\n");
                      fflush(stdin);
                      gets(x.version);
                      printf("\nColor\n");
                      fflush(stdin);
                      gets(x.color);
                      printf("\nPrecio\n");
                      fflush(stdin);
                      scanf("%f", &x.precio);
                      if(autos==0)
                      insertar_vacia(car,x);
                      else
                      {
					  system("cls");
                      printf("\n\n\tDonde desea ingresar el auto\n\n");
                      printf("1. Inicio\n");
                      printf("2. Final\n");
                      if(autos>1)
                      {
                      printf("3. Despues de X\n");
                      printf("4. Antes de X\n");
					}
                      fflush(stdin);
                      scanf("%d", &opi);
                      //----------------CASE DE INSERCION-----------------------
                      switch(opi)
                      {
							case 1:
								if(autos==0)
								insertar_vacia(car, x);
								else
								insertar_inicio(car, x);
								break;
								
							case 2:
								if(autos==0)
								insertar_vacia(car, x);
								else
								insertar_final(car, x);
								break;
								
							case 3:
								printf("\n\nElija posicion\n");
								fflush(stdin);
								scanf("%d", &pos);
								if(pos==autos)
								insertar_final(car, x);
								else if(pos==0)
								insertar_inicio(car, x);
								else if(pos>autos)
								{
								printf("\nPosicion no existente\n");
								system("pause>nul");
								autos--;
							    }
								else
								insertar_despues(car, x, pos);
								break;
								
							case 4:
								printf("\n\nElija posicion\n");
								fflush(stdin);
								scanf("%d", &pos);
								if(pos==1)
								insertar_inicio(car, x);
								else if(pos==autos+1)
								insertar_final(car,x);
								else if(pos>autos+1)
								{
								printf("\nPosicion no existente\n");
								system("pause>nul");
								autos--;
							    }
								else
								insertar_antes(car, x, pos);
								break;
								
							default: printf("\nOpcion incorrecta\n");
							         autos--;
							         system("pause>nul");
					  }
					}
					  system("cls");
					  printf("\n\n");
                      autos++;
                      guardar( car );
                      }
                      else
                      {
                      printf("\nNo se pueden agregar m\240s autos\n");
                      system( "pause>nul" );
                      }
                      break;

             case '2':
					if( !pila_vacia( car ))
					{
                      system( "cls" );
                      printf("\n\n\tDonde se encuentra el auto a eliminar\n\n");
                      printf("1. Inicio\n");
                      printf("2. Final\n");
                      printf("3. Posicion X\n");
                      printf("4. Despues de X\n");
                      printf("5. Antes de X\n");
                      fflush(stdin);
                      scanf("%d", &ope);
                      switch(ope)
                      {
							//------------CASE DE ELIMINACION-------------------
							case 1:
								quitar_inicio( car );
								break;
							case 2:
								quitar_final( car );
								break;
							case 3:
								printf("\n\nElija posicion\n");
								fflush(stdin);
								scanf("%d", &pos);
								if(pos==1)
								quitar_inicio( car );
								else if(pos==autos)
								quitar_final( car );
								else if( pos>autos || pos<1)
								{
								printf("\nPosicion no existente\n");
								system("pause>nul");
								autos++;
							    }
								else
								quitar_nodo( car,pos );
								break;

							case 4:
								printf("\n\nElija posicion\n");
								fflush(stdin);
								scanf("%d", &pos);
								if(pos==0)
								quitar_inicio(car);
								else if(pos==autos-1)
								quitar_final(car);
								else if( pos>=autos )
								{
								printf("\nPosicion no existente\n");
								system("pause>nul");
								autos++;
							    }
								else
								{
									pos=pos+1;
								quitar_nodo(car, pos);
							    }
								break;

							case 5:
								printf("\n\nElija posicion\n");
								fflush(stdin);
								scanf("%d", &pos);
								if(pos==2)
								quitar_inicio(car);
								else if(pos==autos+1)
								quitar_final(car);
								else if( pos<=1 || pos>autos+1)
								{
								printf("\nPosicion no existente\n");
								system("pause>nul");
								autos++;
							    }
								else
								{
									pos=pos-1;
								quitar_nodo(car,pos);
							    }
								break;

							default: printf("\nOpcion incorrecta\n");
							         autos++;
							         system("pause>nul");
					  }
					  system("cls");
					  printf("\n\n");
                      autos--;
                      system("pause");
                      guardar(car);
					}
					else
					printf("\nNo hay inventario\n");
                      system( "pause>nul" );
                      break;

             case '3':
					if( !pila_vacia( car ))
					{
                      system( "cls" );
                      imprimir( car );
					}
					else
					printf("\nNo hay inventario\n");
                      system( "pause>nul" );
                      break;
                      
            case  '4':
                      system( "cls" );
                      if ( lockPila(*car) )
                      {
                      car->estado=1;
                      printf("\nNo se ensamblar\240n mas autos\n");
                      }
                      else
                      {
                      car->estado=0;
                      printf("\nPodr\240 ensamblar m\240s autos\n");
                      }
                      system( "pause>nul" );
                      break;

             case '5':
                      if( !pila_vacia( car ))
                      {
                      system( "cls" );
                      full_pop( car );
                      autos=0;
                      guardar( car );
                      }
                      else
                      printf("\nNo hay inventario\n");
                      system( "pause>nul" );
                      break;
                      
        }
    }while( op != '6' );
    

    system( "cls" );
    printf( "\n\n\t\tFIN DEL PROGRAMA" );
    system( "pause>nul" );
    exit -1;
}

