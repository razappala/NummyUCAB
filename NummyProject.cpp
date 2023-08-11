 			/*****************************************
							Integrantes
				- Maria Valentina Gonzalez Vera
				- Arturo Hung
				- Italo Visconti
				- Rafael Zappala
			*****************************************/

				/*******************************
				 *          Librerias
				*******************************/

				#include <stdio.h>
				#include <stdlib.h>
				#include <conio.h>
				#include <stdbool.h>
				#include <string.h>
				#include <ctype.h>
				#include <time.h>
				#include <unistd.h>


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			const long int maxlongint=2147483647; //maximo numero para un long int
			const int maxint=32767; // maximo numero para un int

			char vacio[2];

			 	typedef struct fechas
				{
					int anio;
					int mes;
					int dia;
				} Fechas;

				typedef struct prodinc
				{
					int codigoPrt;
					int cantidad;
					float precio;
					struct prodinc *prox;
				}  Prodinc;

				typedef struct pedidos
				{
					int factura;
					int codigoEmp;
				    fechas fechas;
					bool entregados;
					float monto_total;
					struct pedidos *prox;
					Prodinc *aba; //multilista
				} Pedidos;

			 	 typedef struct productos
				{
					int codigoPrt;
					char descripcion [21];
					long int precioUd;
					bool activo;
					struct productos *prox;
				} Productos;


				typedef struct personas
				{
					char nombre_apellido [21];
					long int cedula;
					fechas fechas;
					char ciudad [16];
					char direccion [41];
					struct personas *prox;
					Pedidos *aba; //multilista
				} Personas;

				typedef	struct empresas
					{
						int codigoEmp;
						char nombreEmp [21];
						int tipo;
						char tlf [13];
						char direccion [41];
						struct empresas *prox;
						Productos *aba; //multilista
					} Empresas;

				//////////////////////////////////////

					/****************************
					 *  Prototipos de funciones
					 ***************************/
					 
				//////Basicas//////

				void Encabezado ();                      // Rutina para imprimir el encabezado (Nombre de los integrantes)
				void BloqMayus  ( char s[] );            // Rutina para imprimir una cadena de caracteres en formato de mayuscula sostenida
				int validar_num(char numero[]);          // Funcion para validar que la cadena contiene solo numeros
				void ingfecha(int *tanio, int *tmes, int *tdia);  //Rutina para llenar las variables temporales de fecha
				void ingnombre(char *tnombre);			//Rutina para llenar el nombre
				void ingciu(char *tciudad);				//Rutina para llenar la ciudad
				void ingdir(char *tdir);				//Rutina para llenar la direccion
				void ingnum(long int *numero);			//Rutina para llenar la cedula
				void introduciropcion(int *opcion);    //Rutina para introducir opciones del menu
				void prodactivo(bool *act);			//Rutina para llenar la "actividad" de un producto
				void eliminartodoprod(Empresas **emp);	//Rutina para eliminar una lista dinamica completa de productos
				void mostrarproductosemp(Empresas *emp, int codigo); //Rutina para mostrar todos los productos de una empresa
				void eliminartodoprodinc(Pedidos **ped); //Rutina para eliminar todos los productos incluidos de un envio
				void eliminartodoenvio(Personas **per); //Rutina para eliminar todos los envios de una persona
				void imprimirArrayEnteros(long int* const arrayInt, int nroElementosArrayInt);
				void swap(long int* a, long int* b); //Rutina swap utilizada por el ordenamiento burbuja
				void BurbujaEnteros(long int* const arrayInt, int nroElementosInt); //Metodo de ordenamiento burbuja

				  /////Personas//////

				Personas *buscarpersona(Personas *per, long int cedula, char nombre[]); //Funcion para buscar una persona mediante cedula o nombre
				void mostrartodo(Personas *per);            //Rutina para mostrar todas las personas
				void modificarpersona (Personas **per);		//Rutina para modificar persona
				void mostrardatospersona(Personas *per); //Rutina para mostrar datos de una sola persona
				void Eliminarpersona(Personas **per, int cedula); //Rutina para eliminar persona
				void agregarpersona(Personas **per); //Rutina para agregar una persona
				void guardarper(Personas *per); //Rutina para guardar en archivos la lista dinamica de  personas
				void cargarper(Personas **per); //Rutina para llenar la lista de personas con el archivo de personas

					/////Empresas/////

				Empresas *buscarempresa(Empresas *emp, int codigo, char nombre[], int tipo); //Funcion para buscar una empresa mediante codigo, nombre o tipo
 				void mostrartodoemp(Empresas *emp, int tipo);  //Rutina para mostrar todas las empresas
				void ingtipo(int *tipo);	//Rutina para llenar el tipo de una empresa
				void ingtel(char *tlf);    //Rutina para ingresar el numero de telefono
				void ingcodigo(int *codigo); //Rutina para ingresar el codigo
				void agregarempresa(Empresas **emp); //Rutina para agregar empresa
				void modificarempresa(Empresas **emp); //Rutina para modificar empresa
				void mostrardatosempresa(Empresas *emp); //Rutina para mostrar datos de una sola empresa
				void Eliminarempresa(Empresas **emp,int codigo, Personas **per); //Rutina para eliminar empresa
				void guardaremp(Empresas *emp); //Rutina para guardar la lista de  empresas en archivos
				void cargaremp(Empresas **emp); //Rutina para llenar la lista de empresas con el archivo de empresas

					/////Productos//////

				Productos *buscarproductosenempresa(Empresas *emp, int codigo); //Funcion para buscar un producto (en una unica empresa) mediante codigo
				void agregarproducto(Productos **prod, Empresas **emp, int codigo); //Rutina para agregar un producto
				void mostrardatosprod(Productos *prod);	 //Rutina para mostrar los datos de un producto
				void modificarproducto(Productos *prod, Personas **per, int codigo); //Rutina modificar un producto
				void Eliminarproducto(Empresas **emp, int codigo, Personas **per); //Rutina para eliminar un producto

					/////Envios/////

				Prodinc *buscarprodinc(Prodinc *prodinc, int codigo); //Funcion para buscar un producto incluido
				float PrecioTotal (Prodinc *prodinc);	//Funcion para hallar el precio total de un pedido
				bool existeenvio(Personas *per, int codigo); //Funcion para saber si un envio exite o no
				Pedidos *buscarenvios(Personas *per, int factura); //Funcion para buscar un pedido mediante una factura
				void eliminarprodinc (Pedidos **ped, int codigo); //Rutina para eliminar un producto incluido
				void agregarproductoincluido (Prodinc **prodinc, Empresas *emp); //Rutina para agregar un producto incluido
			 	void agregarenvio(Personas **per, Empresas *emp); //Rutina para agregar un envio
				void mostrarfactura (Personas *per, int factura); //Rutina para mostrar una factura
				void cerrarenvio (Personas **per, int copiafactura); //Rutina para cerrar un envio
				void mostrarproductosincluidos (Prodinc *prodinc); //Rutina para mostrar productos incluidos
				void Modificarenvio (Personas **per, int copiafactura, Empresas *emp); //Rutina para modificar un envio
				void eliminarenvio(Personas **per, int factura); //Rutina para eliminar un envio
				void eliminarenvioaux(Personas **per); //Rutina auxiliar para eliminar un envio, validandose codigo de la empresa, cedula del cliente y numero de factura para eliminar

					/////Consultas y extras //////
				
				void infodetodaslasemp(Empresas *emp, Personas *per); //Rutina para mostrar informacion de todas las empresas (4.1.1)
				void Datosemp(int codigo, Personas *per, int *entt, int *noentt, int *clientest, float *ingtotalt, float *promgastadot, int *clientesverift);
				int totalventas(Personas *per,int codigo); //Funcion que devuelve la cantidad de ventas de una empresa en especifico
				float totaling(Personas *per,int codigo, int i); //Funcion que devuelve el ingreso total entregado o no entregado de una empresa
				float promedioproducto(Personas *per,int codigo); //Funcion para conocer el promedio de cantidad de productos por factura
				void infodeunaemp(Empresas *emp, Personas *per); //Rutina que dada una empresa muestra informacion de ella y sus clientes
				void mejorclientetotal(Personas *per);	//Rutina que muestra el mejor cliente por cantidad total percibida
				void mejorclienteproductos (Personas *per); //Rutina que muestra el mejor cliente por cantidad de productos comprados
				void peorclientetotal(Personas *per); //Rutina que muestra el peor cliente por cantidad total NO percibida
				void peorclienteproductos (Personas *per); //Rutina que muestra el peor cliente por cantidad total de productos NO comprados
				void infocliente(Personas *per); //Rutina que dado la cedula de una persona, muestra los detalles de cada pedido realizado
				int contarprod(Personas *per, int codigoPrt, int codigoEmp, int opcion); //Funcion que cuenta la cantidad pedida (Entregada o no dependiendo de su opcion) de un producto en especifico
				void mejoresprod(Empresas *emp, Personas *per); //Rutina que muestra los mejores productos (mas vendido y mejor ingreso)
				void peoresprod(Empresas *emp, Personas *per); //Rutina que muestra los peores productos (menos vendido y peor ingreso)
				void infodeunaper(Personas *per, Empresas *emp);/*Rutina que dada una persona muestra el total de: pedidos hechos, productos adquiridos, monto pagado por los productos. Luego
				se muestran la(s) empresa(s) con el total de facturas, las cantidades de productos y monto de cdaa uno*/
				void infopersona_empresa (Personas *per, Empresas *emp);//Rutina que muestra informacion de una persona relacionada a una empresa
				void infopersona_empresadetallada(Personas *per, Empresas *emp);//Rutina que muestra la informacion de una personas (y sus pedidos) en relacion a una empresa, de forma detallada
				Pedidos *montomasalto(Pedidos *auxped); //Rutina que devuleve la direccion de memoria, donde se encuentra el pedido con el monto mas alto
				void mostrarfacturasentregadas(Personas *per,Pedidos **auxped,Empresas *emp); //Rutina para mostrar los numeros de las facturas entregadas y ordenarlo por monto total o por fecha de emision
				void borrarLista(Pedidos **l); //Rutina para borrar una lista
				Pedidos *fechamasreciente(Pedidos *auxped); //Rutina que devuelve la direccion de memoria, donde se encuentra el pedido con la fecha mas reciente
				Personas *personacantidadmasalta(Personas *tper,int *mayor,int *menor); //Rutina para buscar la persona con la mayor cantidad de productos comprada
				Personas *personamontomasalto(Personas *tper,float *mayor,float *menor); //Rutina para buscar la persona con el mayor monto total de compras realizadas (todos los pedidos entregados)
				void mayorpormonto(Personas **auxper, int a); //Rutina para mostrar las personas con mayor monto gastado 
				void mayorporcantidad(Personas **auxper, int a); //Rutina para mostrar las personas con la mayor cantidad de productos comprados
				void mayoresconsultas(Personas *per, int x); //Rutina para mostrar las personas con mayores montos de compras realizadas y mayor cantidad de productos comprados
				Empresas *empresamayor(int array[],float *ingreso,int a,Personas *per,Empresas *emp); //Funcion que devuelve la empresa con mayor ingreso logrado
                int cantidad ( Personas *per, int codigo ,int z);//Funcion que devuelve la cantidad de productos en facturas entregadas o no entregadas de una empresa en especifico
                void mayoresempresas(Empresas *emp,Personas *per,int z); //Rutina auxiliar para mostrar las empresas con mayores ingresos logrados (4.3.1) y las empresas con mayor cantidad de productos vendidos (4.3.2)
                Empresas *empresacantidad(int array[],int y,Personas *per,Empresas *emp,int *cantidadv); //Funcion que devuelve la empresa con mayor cantidad de productos vendidos

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					int main() {   //   Inicio del programa

					Encabezado ();
					printf("\n\n");
					system("pause");
					system (" cls ");

					system (" color 0F ");
					printf (" \n ");

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					/*******************************
					 *   Declaracion de variables  *
					 ******************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

						/***************************************
						 *   Registros, Punteros y/o Vectores  *
						 **************************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					//   Variables

					char copianombre[21],copianombreEmp[21],copiaop[2],copiaaux[2],copiaaux2[2], copiaopcon[2], copiaconsulta[2],copiaopmod[2],copiaopemtipo[2],copiaactivo[2],copiaopemtipo1[2];
					int titulo = 0;
					int op, aux, aux2, opcon, consulta, opmod, copiape;
					int tanio, tmes, tdia, tcedula;
					char tciu[16], tdir[41], tnombre[21];
					int activo, copiacodigo,copiatipo,x;
					long int copiacedula,valn;
					int copiafactura;
					int copiaempresa, copiaproducto;

						Productos *prod=NULL, productos;
						Empresas *emp=NULL, empresas;
						Personas *per=NULL, personas;
						Pedidos *ped=NULL, pedidos;
						Pedidos *auxped=NULL; //Lista auxiliar para consultas
						Prodinc *prodinc=NULL, prodInc;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				cargarper(&per);
				cargaremp(&emp);

					do {

						if (titulo==0){
							printf("  BIENVENIDOS A YUMMY!!!\n\n");
							titulo++;
						} else	printf("\t YUMMY \n\n");

						printf("\t MENU\n\n");

						printf(" 1- PERSONAS\n 2- EMPRESAS Y PRODUCTOS\n 3- ORDENES DE ENVIO\n 4- CONSULTAS\n\n 0- SALIR\n\n ");

						fflush(stdin);
						introduciropcion(&op);

						system("cls");
						switch (op) {

							//Personas
								case 1:
									do {
										printf("\n\tPERSONAS\n\n");
										printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");

										switch (aux)
										{
											case 0:
											break;
											//Agregar Persona
											case 1: printf("\n\tAGREGAR\n\n");
													agregarpersona(&per);
													system("cls");
													printf("\n\n\tPERSONA AGREGADA CON EXITO!!!\n\n");
											break;
											//Modificar Persona
											case 2 : printf("\n\tMODIFICAR\n\n");
													if (per)
														modificarpersona(&per);
													else  printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");
											break;
											//Consultar Persona
											case 3: printf("\n\tCONSULTAR\n\n");
													copiacedula=0;
													if (per) {
														printf(" MEDIANTE QUE OPCION DESEA CONSULTAR?\n");
														printf(" 1- CEDULA\n 2- NOMBRE Y APELLIDO \n");

														do {
															fflush(stdin);
															introduciropcion(&consulta);
														} while(consulta!=1 && consulta!=2);
														system("cls");
														switch (consulta)
														{
														//Cedula
														case 1: printf("\n\n INGRESE EL NUMERO DE CEDULA DE LA PERSONA: ");
																ingnum(&copiacedula);
																printf("\n\n");
														break;
														//Nombre y Apellido
														case 2:
																printf("\n\n INGRESE EL NOMBRE Y APELLIDO DE LA PERSONA A CONSULTAR: ");
																ingnombre(copianombre);
														break;
														}
												mostrardatospersona(buscarpersona(per, copiacedula, copianombre));
												/*Para consultar, en caso buscarpersona es una funcion que nos devolvera
												un apuntador de donde esta la persona que se desea consultar, ese apuntador lo recibe
												la funcion mostrardatospersona que imprimira por pantalla los datos de la persona*/
													} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");

											break;
											//Eliminar Persona
											case 4: printf("\n\tELIMINAR\n\n");
													if (per)
													 {
														printf(" INGRESE LA CEDULA DE LA PERSONA A ELIMINAR: ");
														ingnum(&copiacedula);
															if (buscarpersona(per, copiacedula, vacio))
															{
																Eliminarpersona(&per, copiacedula);
																system("cls");
								 								printf("\n\tPERSONA ELIMINADA CON EXITO!!!\n\n");
															} else
															{
																printf("\n NO EXISTE NINGUNA PERSONA CON EL NUMERO DE CEDULA INGRESADO\n\n");
															}
													} else printf(" NO EXISTE NINGUNA PERSONA EN EL SISTEMA\n\n");
											break;
											default:
													printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
										}    // Fin del 1er Switch
										if (aux !=0)
										{
											system("pause");
		    								system("cls");
										}

										}

								while(aux !=0);

								break;

				/////////////////////////////////////////////////////////////////////////////////

							//Empresas y Productos
								case 2 :
									do {
										printf("\n\tEMPRESAS Y PRODUCTOS\n\n");
										printf(" 1- EMPRESAS\n 2- PRODUCTOS\n\n 0- VOLVER\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");

										switch (aux) {
											case 0:
											break;
											//Empresas 2.1
											case 1:
													do {
														printf("\n\tEMPRESAS \n\n");
														printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
														fflush(stdin);
														introduciropcion(&aux2);
														system("cls");

														switch (aux2) {
															case 0:
															break;
															//Agregar Empresa
															case 1:
																	printf("\n\tAGREGAR\n\n");
																	agregarempresa(&emp);
																	fflush(stdin);
																	system("cls");
																	printf("\n\n\tEMPRESA AGREGADA CON EXITO!!!\n\n");
															break;
															//Modificar Empresa
															case 2:
																	printf("\n\tMODIFICAR\n\n");
																	if (emp)
																	   	modificarempresa(&emp);
																	else  printf(" NO EXISTE NINGUNA EMPRESA EN EL SISTEMA\n\n");
															break;
															//Consultar Empresa
															case 3:
																	printf("\n\tCONSULTAR\n\n");
																	copiacodigo=0;

																	if (emp)
																	{
																		printf(" MEDIANTEQUE OPCION DESEA CONSULTAR?\n");
																		printf(" 1- CODIGO\n 2- NOMBRE DE LA EMPRESA \n ");

																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																		system("cls");
																	switch (consulta)
																	{
																		//Codigo
																	    case 1:
																				printf("\n\n INGRESE EL CODIGO DE LA EMPRESA: ");
																				ingcodigo(&copiacodigo);
																		break;
																		//Nombre de la empresa
																		case 2:
																				printf("\n\n INGRESE EL NOMBRE DE LA EMPRESA: ");
																				ingnombre(copianombre);
																		break;
																	}
																mostrardatosempresa(buscarempresa(emp,copiacodigo,copianombre, 0));
																/*Para consultar, en caso buscarempresa es una funcion que nos devolvera
																un apuntador de donde esta la empresa que se desea consulta, ese apuntador lo recibe
																la funcion mostrardatosempresa que imprimira por pantalla los datos de la empresa*/
																	} else
																			{
																			printf(" NO EXISTE NINGUNA EMPRESA EN EL SISTEMA\n\n");
																			}

															break; //Consultar

															//Eliminar Empresa
															case 4:
																printf("\n\tELIMINAR\n\n");
																if (emp)
																{
																	printf(" INGRESE EL CODIGO DE LA EMPRESA A ELIMINAR: ");
																	ingcodigo(&copiaempresa);
																	Eliminarempresa(&emp,copiaempresa, &per);
																}
																else {
																	printf(" NO EXISTE NINGUNA EMPRESA EN EL SISTEMA \n\n");
																}
															break;

														default:printf(" DEBE ELEGIR UNA OPCION VALIDA ");
																sleep(2);
														}
														if (aux2 !=0)
														{
														system("pause");
														system("cls");
														}

														} while (aux2 !=0);

								break; //empresas

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

								//Productos 2.2
								case 2:
										if (emp==NULL)
										{
											printf("\n NO EXISTE NINGUNA EMPRESA EN EL SISTEMA\n\n");
											system("pause");
											break;
										}

										do{
											printf("\n\tPRODUCTOS \n\n");
											printf(" 1- AGREGAR\n 2- MODIFICAR\n 3- CONSULTAR\n 4- ELIMINAR\n\n 0- VOLVER\n\n ");
											fflush(stdin);
											introduciropcion(&aux2);
											system("cls");
											switch (aux2)
											{
												case 0:
												break;
												//Agregar Producto
												case 1:
														fflush(stdin);
														printf("\n\tAGREGAR\n\n");
														int codigocopia;
														printf(" A QUE EMPRESA PERTENECE ESTE PRODUCTO? (INGRESE SU CODIGO): ");
														ingcodigo(&codigocopia);
														printf("\n");
														if (buscarempresa(emp, codigocopia, copianombre, 0)==NULL) {
															 printf(" LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA \n\n");
														} else { agregarproducto(&prod, &emp, codigocopia); }
												break;
												//Modificar Producto
												case 2:
														printf("\n\tMODIFICAR\n\n");
														Empresas *temp1;
														Productos *prod1;
														printf(" A QUE EMPRESA PERTENECE ESTE PRODUCTO? (INGRESE SU CODIGO): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp1=buscarempresa(emp,codigocopia,copianombre,0);
															if (temp1)
															{
																printf(" EMPRESA: %s\n\n", temp1->nombreEmp);
																printf(" INTRODUZCA EL CODIGO DEL PRODUCTO A MODIFICAR: ");
																ingcodigo(&copiacodigo);
																prod1=buscarproductosenempresa(temp1,copiacodigo);
																modificarproducto(prod1, &per, temp1->codigoEmp);
															}
															else{printf(" LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA\n\n");}
												break;

												//Consultar Producto
												case 3:
														printf("\n\tCONSULTAR\n\n");
														Empresas *temp2;
														Productos *prod2;
														printf(" A QUE EMPRESA PERTENECE ESTE PRODUCTO? (INGRESE SU CODIGO): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp2=buscarempresa(emp,codigocopia,copianombre,0);
														if (temp2)
														{
															printf(" EMPRESA: %s\n\n", temp2->nombreEmp);
															printf(" INTRODUZCA EL CODIGO DEL PRODUCTO A CONSULTAR: ");
															ingcodigo(&copiacodigo);
															prod2=buscarproductosenempresa(temp2,copiacodigo);
															mostrardatosprod(prod2);
														}
														else{printf(" LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA\n\n");}
												break;

												//Eliminar Producto
												case 4:
														printf("\n\tELIMINAR\n\n");
														Empresas *temp;
														Productos *prod;
														printf(" A QUE EMPRESA PERTENECE ESTE PRODUCTO? (INGRESE SU CODIGO): ");
														ingcodigo(&codigocopia);
														printf("\n");
														temp=buscarempresa(emp,codigocopia,copianombre,0);
														if (temp)
														{
															printf(" EMPRESA: %s\n\n", temp->nombreEmp);
															printf(" INTRODUZCA EL CODIGO DEL PRODUCTO A ELIMINAR: ");
															ingcodigo(&copiacodigo);
															prod=buscarproductosenempresa(temp,copiacodigo);
															if(prod){
																Eliminarproducto(&temp,copiacodigo, &per);
															} else {printf("\n EL PRODUCTO NO SE ENCUENTRA EN EL SISTEMA\n");}
														}
														else{printf(" LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA\n\n");}
												break;

											default: printf(" DEBE ELEGIR UNA OPCION VALIDA ");
													sleep(2);
											}

												if (aux2 !=0)
													{
													system("pause");
													system("cls");
													}

											}while(aux2!=0);
												break;
												default: printf(" DEBE ELEGIR UNA OPCION VALIDA ");
												sleep(2);
											}
									system("cls");
										}
						while(aux!=0);

				/////////////////////////////////////////////////////////////////////////////////

						break;

				/////////////////////////////////////////////////////////////////////////////////

							//Ordenes de envio
							case 3:
								if ((per==NULL)||(emp==NULL))
								{
									printf("\n PRIMERO SE DEBEN AGREGAR PERSONAS Y/O EMPRESAS \n\n");
									system("pause");
								break;
								}
								do {
									printf("\n\tORDENES DE ENVIO\n\n");
									printf(" 1- SOLICITAR ENVIO\n 2- MODIFICAR ENVIO\n 3- CONSULTAR ENVIO\n 4- CIERRE DE ENVIO\n 5- ELIMINAR ENVIO\n\n 0- VOLVER\n\n ");
									fflush(stdin);
									introduciropcion(&aux);
									system("cls");
									switch (aux) {
										case 0:
										break;
										//Solicitar envio 3.1
										case 1:
												printf("\n\tSOLICITAR ENVIO \n\n");
												agregarenvio(&per, emp);
										break;
										//Modificar Envio 3.2
										case 2:
												printf("\n\tMODIFICAR ENVIO \n\n");
												printf(" INGRESE EL NUMERO DE FACTURA:  ");
												ingcodigo(&copiafactura);
												if (buscarenvios(per, copiafactura)==NULL)
												{
													printf("\n EL PEDIDO CON ESE NUMERO DE FACTURA NO SE ENCUENTRA EN EL SISTEMA \n\n");
													system("pause");
													break;
												}
												system("cls");
												Modificarenvio (&per, copiafactura, emp);
										break;
										//Consultar Envio 3.3
										case 3:
												printf("\n\tCONSULTAR ENVIO \n\n");
												printf(" INGRESE EL NUMERO DE FACTURA: ");
												ingcodigo(&copiafactura);
												if (buscarenvios(per, copiafactura)==NULL)
												{
													printf("\n EL PEDIDO CON ESE NUMERO DE FACTURA NO SE ENCUENTRA EN EL SISTEMA\n\n");
													system("pause");
													break;
												}
												system("cls");
												mostrarfactura(per, copiafactura);
										break;
										//Cierre de envio 3.4
										case 4:
												printf("\n\tCIERRE DE ENVIO \n\n");
												printf(" INGRESE EL NUMERO DE FACTURA: ");
												ingcodigo(&copiafactura);
												cerrarenvio (&per, copiafactura);
										break;
										//Eliminar un Envio 3.5
										case 5:
												printf("\n\tELIMINAR ENVIO \n\n");
												eliminarenvioaux(&per);
										break;
										default: printf(" DEBE ELEGIR UNA OPCION VALIDA \n\n");
										}
										system("cls");
										}
										while(aux!=0);
							break;

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

							//Consultas
							case 4:
									do {
										printf("\n\tCONSULTAS\n\n");
										printf(" 1- EMPRESAS\n 2- PERSONAS\n 3- SISTEMA\n\n 0- VOLVER\n\n ");
										fflush(stdin);
										introduciropcion(&aux);
										system("cls");
										switch (aux) {
											case 0:
											break;
											//Empresas 4.1
											case 1:
													if 	(!(existeenvio(per,0)))
													{
														printf("\n\tEMPRESAS\n\n");
														printf(" NO EXISTE NINGUN PEDIDO EN EL SISTEMA\n\n");
														system("pause");
														break;
													}
													do {
														printf("\n\tEMPRESAS\n\n");
														printf(" 1- INFORMACION DE TODAS LAS EMPRESAS (4.1.1)\n 2- INFORMACION DE UNA EMPRESA (4.1.2)\n 3- INFORMACION DE UN CLIENTE (4.1.3)\n 4- MOSTRAR MEJOR/PEOR CLIENTE (4.1.4)\n 5- MOSTRAR MEJOR/PEOR PRODUCTO (4.1.5)\n\n 0- VOLVER\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Info de todas las Empresas 4.1.1
															case 1:
																	printf("\n\tINFORMACION DE TODAS LAS EMPRESAS (4.1.1) \n\n");
																		
																		infodetodaslasemp(emp, per);
																		
																	system("pause");
															break;
															//Info de una Empresa 4.1.2
															case 2:
																	printf("\n\tINFORMACION DE UNA EMPRESA (4.1.2)\n\n");
																	copiacodigo=0;
																	printf(" MEDIANTE QUE OPCION DESEA CONSULTAR?\n");
																	printf(" 1- CODIGO\n 2- NOMBRE DE LA EMPRESA \n ");
																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																	system("cls");
																	switch (consulta){
																		//Codigo
																		case 1:
																				printf("\n\n INGRESE EL CODIGO DE LA EMPRESA: ");
																				ingcodigo(&copiacodigo);
																		break;
																		//Nombre de la empresa
																		case 2:
																				printf("\n\n INGRESE EL NOMBRE DE LA EMPRESA: ");
																				ingnombre(copianombre);
																		break;
																	}
																	Empresas *pemp;
																	pemp = buscarempresa(emp,copiacodigo,copianombre, 0);
																	if (pemp){
																		if 	(!(existeenvio(per, pemp->codigoEmp))) {
																			printf(" NO EXISTE NINGUN PEDIDO HACIA ESTA EMPRESA EN EL SISTEMA\n\n");
																			system("pause");
																			break;
																		}
																		infodeunaemp(pemp, per);
																	} else {printf("\n LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA\n\n");}
																	system("pause");
															break;
															//Info de un Cliente 4.1.3
															case 3:
																	printf("\n\tINFORMACION DE UN CLIENTE (4.1.3)\n\n");
																	infocliente(per);
																	printf("\n");
																	system("pause");
															break;
															system("pause");
															break;
															//Mostrar Mejor/Peor Cliente 4.1.4
															case 4:
																	printf("\n\tMOSTRAR MEJOR/PEOR CLIENTE (4.1.4)\n\n");
																	printf("----------------------------------------------------------------\n\n");
																	//Mejor cliente por cantidad total percibida
																	mejorclientetotal(per);
																	printf("----------------------------------------------------------------\n\n");
																	//Mejor cliente por cantidad de productos comprados
																	mejorclienteproductos (per);
																	printf("----------------------------------------------------------------\n\n");
																	//Peor cliente por cantidad total no percibida
																	 peorclientetotal(per);
																	printf("----------------------------------------------------------------\n\n");
																	//Peor cliente por cantidad de productos no comprados
																	peorclienteproductos (per);
																	printf("----------------------------------------------------------------\n\n");
																	system("pause");
															break;
															system("pause");
															break;
															//Mostrar Mejor/Peor Producto 4.1.5
															case 5:
																	printf("\n\tMOSTRAR MEJOR/PEOR PRODUCTO (4.1.5)\n\n");
																	mejoresprod(emp, per);
																	peoresprod(emp, per);
																	system("pause");
															break;
															default: printf(" DEBE ELEGIR UNA OPCION VALIDA \n");
																	sleep(2);
															}
															system("cls");
															} while(opcon!=0);
															break;
											//Personas 4.2
											case 2:
													do {
														printf("\n\tPERSONAS\n\n");
														printf(" 1- INFORMACION SOBRE UNA PERSONA (4.2.1)\n 2- INFORMACION PERSONA/EMPRESA (4.2.2)\n\n 0- VOLVER\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Info sobre una Persona 4.2.1
															case 1:
																	copiacedula=0;
																	printf("\n\tINFORMACION SOBRE UNA PERSONA (4.2.1)\n\n");
																	printf(" MEDIANTE QUE OPCION DESEA CONSULTAR?\n");
																	printf(" 1- CEDULA\n 2- NOMBRE Y APELLIDO  \n ");
																	do {
																		fflush(stdin);
																		introduciropcion(&consulta);
																		if (consulta!=1 && consulta!=2) {
																			printf("\n\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS \n ");

																		}
																	} while(consulta!=1 && consulta!=2);
																	system("cls");
																	switch (consulta){
																		//Cedula
																		case 1:
																				printf("\n\n INGRESE EL NUMERO DE CEDULA DE LA PERSONA: ");
																				ingnum(&copiacedula);
																		break;
																		//Nombre
																		case 2:
																				printf("\n\n INGRESE EL NOMBRE Y APELLIDO DE LA PERSONA A CONSULTAR: ");
																				ingnombre(copianombre);
																		break;
																	}
																	if (buscarpersona(per, copiacedula, copianombre)){
																		infodeunaper(buscarpersona(per, copiacedula, copianombre), emp);
																	} else {
																			printf("\n LA PERSONA NO SE ENCUENTRA EN EL SISTEMA \n\n");
																			}
																	system("pause");
															break;
															// Info Persona/Empresa 4.2.2
															case 2:
																copiacedula=0;
																copiacodigo=0;
																char copianombre2[21];
																printf("\n\tINFORMACION PERSONA/EMPRESA (4.2.2)\n\n");
																printf(" Persona: \n\n");
																//Persona
																printf(" MEDIANTE QUE OPCION DESEA CONSULTAR?\n");
																printf(" 1- CEDULA\n 2- NOMBRE Y APELLIDO \n ");
																do {
																	fflush(stdin);
																	introduciropcion(&consulta);
																	if (consulta!=1 && consulta!=2) {
																		printf("\n\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS \n ");

																	}
																} while(consulta!=1 && consulta!=2);
																system("cls");
																switch (consulta){
																	//Cedula
																	case 1:
																			printf("\n\n INGRESE EL NUMERO DE CEDULA DE LA PERSONA: ");
																			ingnum(&copiacedula);
																	break;
																	//Nombre
																	case 2:
																			printf("\n\n INGRESE EL NOMBRE Y APELLIDO DE LA PERSONA A CONSULTAR: ");
																			ingnombre(copianombre);
																	break;
																}
																system("cls");
																printf("\n\tINFORMACION PERSONA/EMPRESA \n\n");
																printf(" Empresa: \n\n");
																//empresa
																printf(" MEDIANTE QUE OPCION DESEA CONSULTAR?\n");
																printf(" 1- CODIGO\n 2- NOMBRE DE LA EMPRESA \n ");
																do {
																	fflush(stdin);
																	introduciropcion(&consulta);
																	if (consulta!=1 && consulta!=2) {
																		printf("\n\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS \n ");

																	}
																} while(consulta!=1 && consulta!=2);
																system("cls");
																switch (consulta){
																	//Codigo
																	case 1:
																			printf("\n\n INGRESE EL CODIGO DE LA EMPRESA: ");
																			ingcodigo(&copiacodigo);
																	break;
																	//Nombre de la empresa
																	case 2:
																			printf("\n\n INGRESE EL NOMBRE DE LA EMPRESA: ");
																			ingnombre(copianombre2);
																	break;
																}
																if ((!buscarpersona(per, copiacedula, copianombre)) || (!buscarempresa(emp, copiacodigo, copianombre2, 0))) {
																	printf("\n LA PERSONA Y/O EMPRESA NO SE ENCUENTRA EN EL SISTEMA\n\n");
																	system("pause");
																	break;
																}
																infopersona_empresadetallada(buscarpersona(per, copiacedula, copianombre), buscarempresa(emp, copiacodigo, copianombre2, 0));
																system("pause");
															break;
															default: printf("  DEBE ELEGIR UNA OPCION VALIDA \n");
																	sleep(2);
															}
														   system("cls");
															} while(opcon!=0);
											break;
											//Sistema 4.3
											case 3:
													do {
														printf("\n\tSISTEMA\n\n");
														printf(" 1- MOSTRAR LAS EMPRESAS CON LOS MAYORES INGRESOS LOGRADOS (4.3.1)\n 2- MOSTRAR LAS EMPRESAS CON LA MAYOR CANTIDAD DE PRODUCTOS VENDIDOS (4.3.2)\n 3- MOSTRAR LAS PERSONAS CON LOS MAYORES MONTOS DE COMPRAS REALIZADAS (4.3.3)\n 4- MOSTRAR LAS PERSONAS CON MAYOR CANTIDAD DE PRODUCTOS COMPRADOS (4.3.4)\n 5- MOSTRAR NUMERO DE FACTURAS ENTREGADAS (4.3.5)\n\n 0- VOLVER\n\n ");
														fflush(stdin);
														introduciropcion(&opcon);
														system("cls");
														switch (opcon) {
															case 0:
															break;
															//Mostrar las Empresas con los mayores ingresos logrados 4.3.1
															case 1:
																	printf("\n\tMOSTRAR LAS EMPRESAS CON LOS MAYORES INGRESOS LOGRADOS (4.3.1)\n\n");
																	mayoresempresas(emp,per,1);
																	system("pause");
															break;

															//Mostrar las Empresas con la mayor cantidad de productos vendidos 4.3.2
															case 2:
																	printf("\n\tMOSTRAR LAS EMPRESAS CON LA MAYOR CANTIDAD DE PRODUCTOS VENDIDOS (4.3.2)\n\n");
																	mayoresempresas(emp,per,2);
																	system("pause");
															break;

															//Mostrar las personas con los mayores montos de compras realizadas 4.3.3
															case 3:
																	printf("\n\tMOSTRAR LAS PERSONAS CON LOS MAYORES MONTOS DE COMPRAS REALIZADAS (4.3.3)\n\n");																	
																	mayoresconsultas(per,1);
																	system("pause");
															break;


															//Mostrar las personas con mayor cantidad de productos comprados 4.3.4
															case 4:
																	printf("\n\tMOSTRAR LAS PERSONAS CON MAYOR CANTIDAD DE PRODUCTOS COMPRADOS (4.3.4)\n\n");
																	 mayoresconsultas(per, 2);
																	system("pause");
															break;


															//Mostrar facturas entregadas 4.3.5 revisar cuando no hay facturas
															case 5:
																	
																	printf("\n\tMOSTRAR FACTURAS ENTREGADAS (4.3.5)\n\n");
																	if(existeenvio(per, 0)){
																		mostrarfacturasentregadas(per,&auxped,emp);
																	}
																	else{
																		printf("\n NO EXISTE NINGUNA FACTURA EN EL SISTEMA \n");
																	}

																	system("pause");
																	system ("cls");
															break;
															default: printf(" DEBE ELEGIR UNA OPCION VALIDA \n");
																	 sleep(2);
															}
															system("cls");
															 } while(opcon!=0);
												break;
												default: printf(" DEBE ELEGIR UNA OPCION VALIDA \n");
														sleep(2);
														}
											system("cls");
										} while(aux!=0);
					  		  break;

				/////////////////////////////////////////////////////////////////////////////////
				default:
						if (op != 0)
						{
							printf(" DEBE ELEGIR UNA OPCION VALIDA ");
							sleep(2);
						}
					}
					system("cls");

				}
					while(op !=0);
				/////////////////////////////////////////////////////////////////////////////////

				guardarper(per);
				guardaremp(emp);

				printf("\n HASTA PRONTO!!!\n");
				return 0;

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				}      //   Fin del programa

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

					/*******************************
					 *   Declaracion de funciones
					 ******************************/

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void Encabezado ()
					{
						system (" color 0A");
						printf (" \n ");
						printf ("\t  UNIVERSIDAD CATOLICA ANDRES BELLO \n\t    ALGORITMOS Y PROGRAMACION II \n\n\t     MARIA VALENTINA GONZALEZ  \n \t \t    ARTURO HUNG \n\t \t   ITALO VISCONTI\n\t \t   RAFAEL ZAPPALA");
						printf("\n\n |CONTAMOS CON GUARDADO AUTOMATICO AL FINALIZAR EL PROGRAMA ;)|");
					}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*guardarper es una funcion que nos permite al final de cada programa, guardar en un archivo la lista de persona*/
				void guardarper(Personas *per){

					FILE *personas;
				  	personas = fopen ("personas.txt","w");

						if (personas == NULL){
						printf("\n ERROR! NO SE HA PODIDO CREAR EL ARCHIVO\n\n");
						system("pause");
						return;
						} else
							for ( ; per; per=per->prox){	//Personas
								fprintf(personas, "%li\n", per->cedula);
								fprintf(personas, "%s\n", per->nombre_apellido);
								fprintf(personas, "%i\n", per->fechas.anio);
								fprintf(personas, "%i\n", per->fechas.mes);
								fprintf(personas, "%i\n", per->fechas.dia);
								fprintf(personas, "%s\n", per->ciudad);
								fprintf(personas, "%s\n", per->direccion);

								Pedidos *ped;
								ped = per->aba;
									for ( ; ped; ped=ped->prox){	//Pedidos
										fprintf(personas, "%i\n", ped->codigoEmp);
										fprintf(personas, "%i\n", ped->entregados);
										fprintf(personas, "%i\n", ped->factura);
										fprintf(personas, "%i\n", ped->fechas.anio);
										fprintf(personas, "%i\n", ped->fechas.mes);
										fprintf(personas, "%i\n", ped->fechas.dia);
										fprintf(personas, "%f\n", ped->monto_total);
										Prodinc *prodinc;
										prodinc = ped->aba;
										for ( ; prodinc; prodinc=prodinc->prox){
											fprintf(personas, "%i\n", prodinc->codigoPrt);
											fprintf(personas, "%i\n", prodinc->cantidad);
											fprintf(personas, "%f\n", prodinc->precio);
										}
										fprintf(personas, "0\n");
									}
									fprintf(personas, "0\n");
							}
							fprintf(personas, "0\n");
					fclose(personas);
				}
				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*cargarper es una funcion que nos permite, al inicio de cada programa vaciar el archivo de personas en la lista de personas,*/
				void cargarper(Personas **per){
					Personas *tper = new Personas;
					Pedidos *ped, *tped;
					Prodinc *prodinc, *tprodinc;

					char x[1];
					long int nuloper;
					int nuloped, nuloprodinc;
					FILE *personas;

					if((personas=fopen("personas.txt", "r"))==NULL){
						printf("\n\t ES LA PRIMERA VEZ ENTRANDO A YUMMY :) \n\n    [ESTA A PUNTO DE DESCUBRIR EL FUTURO EN DELIVERY] \n\n");
						system("pause"); system("cls");
					} else {
							fscanf(personas, " ", &x); 	//Para evitar un caso borde (.txt en blanco) leemos el primer "caracter" en este, para de esta manera NO entrar en el while y llegar al 'eof'
													   //de esta forma evitamos la impresion erronea del archivo en la lista
							fscanf(personas, "%li\n", &nuloper);
							while ((nuloper!=0)&&(!(feof(personas)))) {		//Personas
									tper->cedula = nuloper;
									fscanf(personas, " %[^\n]s\n", &tper->nombre_apellido);
									fscanf(personas, "%i\n", &tper->fechas.anio);
									fscanf(personas, "%i\n", &tper->fechas.mes);
									fscanf(personas, "%i\n", &tper->fechas.dia);
									fscanf(personas, " %[^\n]s\n", &tper->ciudad);
									fscanf(personas, " %[^\n]s\n", &tper->direccion);
									tper->aba = NULL;
									ped = tper->aba;

									fscanf(personas, "%i\n", &nuloped);
										while (nuloped!=0){				//Pedidos
											tped = new Pedidos;
											tped->codigoEmp = nuloped;
											fscanf(personas, "%i\n", &tped->entregados);
											fscanf(personas, "%i\n", &tped->factura);
											fscanf(personas, "%i\n", &tped->fechas.anio);
											fscanf(personas, "%i\n", &tped->fechas.mes);
											fscanf(personas, "%i\n", &tped->fechas.dia);
											fscanf(personas, "%f\n", &tped->monto_total);

											tped->aba = NULL;
											prodinc = tped->aba;

											fscanf(personas, "%i\n", &nuloprodinc);
												while (nuloprodinc!=0){		//Productos Incluidos
													tprodinc = new Prodinc;
													tprodinc->codigoPrt = nuloprodinc;
													fscanf(personas, "%i\n", &tprodinc->cantidad);
													fscanf(personas, "%f\n", &tprodinc->precio);
													if (prodinc){
													tprodinc->prox = prodinc;
													} else {
													tprodinc->prox = NULL;
													}
													tped->aba = tprodinc;
													prodinc = tprodinc;

													fscanf(personas, "%i\n", &nuloprodinc);
												}

											if (ped){
											tped->prox = ped;
											} else {
											tped->prox = NULL;
											}
											tper->aba = tped;
											ped = tped;

										fscanf(personas, "%i\n", &nuloped);
										}

									if (*per){
									tper->prox = *per;
									} else {
									tper->prox = NULL;
									}
									*per=tper;

									fscanf(personas, "%i\n", &nuloper);
									if (nuloper!=0) tper=new Personas;
							}
					}
						fclose(personas);

				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                /*guardaremp es una funcion que nos permite al final de cada programa, guardar en un archivo la lista de empresas*/
				void guardaremp(Empresas *emp){

					FILE *empresas;

					if ((empresas=fopen("empresas.txt", "w"))==NULL){
						printf("\n ERROR! NO SE HA PODIDO CREAR EL ARCHIVO\n\n");
						system("pause");
						return;
					}
					else
						for ( ; emp; emp=emp->prox){
							fprintf(empresas, "%i\n", emp->codigoEmp);
							fprintf(empresas, "%s\n", emp->nombreEmp);
							fprintf(empresas, "%i\n", emp->tipo);
							fprintf(empresas, "%s\n", emp->tlf);
							fprintf(empresas, "%s\n", emp->direccion);
								Productos *prod;
								prod = emp->aba;
								for ( ; prod; prod=prod->prox){
									fprintf(empresas, "%i\n", prod->codigoPrt);
									fprintf(empresas, "%s\n", prod->descripcion);
									fprintf(empresas, "%i\n", prod->activo);
									fprintf(empresas, "%li\n", prod->precioUd);
								}
								fprintf(empresas, "0\n");

						}
					fprintf(empresas, "0");
					fclose(empresas);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*cargaremp es una funcion que nos permite, al inicio de cada programa vaciar el archivo de empresas en la lista de empresas*/
				void cargaremp(Empresas **emp){

					Empresas *temp = new Empresas;
					Productos *prod, *tprod;

					char x[1];
					int nuloemp, nuloprod;
					FILE *empresas;

					if((empresas=fopen("empresas.txt", "r"))==NULL){

					} else {
							fscanf(empresas, " ", &x); 	//Para evitar un caso borde (.txt en blanco) leemos el primer "caracter" en este, para de esta manera NO entrar en el while y llegar al 'eof'
													   //de esta forma evitamos la impresion erronea del archivo en la lista
							fscanf(empresas, "%i\n", &nuloemp);
							while ((nuloemp!=0)&&(!(feof(empresas)))) { //Empresas
									temp->codigoEmp = nuloemp;
									fscanf(empresas, " %[^\n]s\n", &temp->nombreEmp);
									fscanf(empresas, "%i\n", &temp->tipo);
									fscanf(empresas, "%s\n", &temp->tlf);
									fscanf(empresas, " %[^\n]s\n", &temp->direccion);

									temp->aba = NULL;
									prod = temp->aba;

									fscanf(empresas, "%i\n", &nuloprod);
										while (nuloprod!=0){		//Productos
											tprod = new Productos;
											tprod->codigoPrt = nuloprod;
											fscanf(empresas, " %[^\n]s\n", &tprod->descripcion);
											fscanf(empresas, "%i\n", &tprod->activo);
											fscanf(empresas, "%li\n", &tprod->precioUd);

											if (prod){
											tprod->prox = prod;
											} else {
											tprod->prox = NULL;
											}
											temp->aba = tprod;
											prod = tprod;

										fscanf(empresas, "%i\n", &nuloprod);
										}

									if (*emp){
									temp->prox = *emp;
									} else {
									temp->prox = NULL;
									}
									*emp=temp;

									fscanf(empresas, "%i\n", &nuloemp);
									if (nuloemp!=0) temp=new Empresas;
							}
					}
						fclose(empresas);
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que convierte todas las letras de un string en mayusculas*/
					void  BloqMayus ( char s[] )	{
						int i;
						for (i = 0; s[i]!='\0'; i++)
						{
							if(s[i] >= 'a' && s[i] <= 'z')
								{
								s[i] = s[i] - 32;
								}
						}
					}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que nos permite validar dado un string, saber si tiene solo numeros o contiene letras*/
					int validar_num (char numero[])	{
							int i=0, sw=0,j;
							j=strlen(numero);
							while((i<j)&&(sw==0)){
								if(isdigit(numero[i])!=0){
									i++;
								}
								else
									{
										sw=1;
									}
							}
							return sw;
						}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que nos permite calcular el monto total de un pedido*/
					float PrecioTotal (Prodinc *prodinc) {
						float cont = 0;
							for ( ; prodinc; prodinc=prodinc->prox){
								cont += ((prodinc->precio)*(prodinc->cantidad));
							}
						return cont;
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar el ingreso de fechas, tanto que este en el rango (1900-2100) y no contenta letras*/
					void ingfecha(int *tanio, int *tmes, int *tdia) {
						char copia[5],copia1[3],copia2[3];
						int valn;

							do{
								printf("\n ANIO: ");
								scanf("%s",&copia);
								valn=validar_num(copia);
								*tanio=atoi(copia);
								if ((valn!=0)||(*tanio<1900)||(*tanio>2100)) printf("\n EL ANIO DEBE ESTAR ENTRE 1900 Y 2100\n");
							}while((valn!=0)||(*tanio<1900)||(*tanio>2100));
							printf  (" \n");
							do{
								printf (" MES: ");
								scanf ("%s",&copia1);
								valn=validar_num(copia1);
								*tmes=atoi(copia1);
								if ((valn!=0)||(*tmes<=0) || (*tmes>12)) printf("\n EL MES DEBE ESTAR ENTRE 1 Y 12\n\n");
							} while((valn!=0)||(*tmes<=0) || (*tmes>12));
							printf  (" \n");
							do{
								printf (" DIA: ");
								scanf ("%s",&copia2);
								valn=validar_num(copia2);
								*tdia=atoi(copia2);
								if ((valn!=0)||(*tdia<=0) || (*tdia>31)) printf("\n EL DIA DEBE ESTAR ENTRE 1 Y 31\n\n");
							} while ((valn!=0)||(*tdia<=0) || (*tdia>31));
							printf  (" \n");
							fflush(stdin);

					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que el nombre no excede la cantidad de 20 caracteres*/
					void ingnombre(char *tnombre) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tnombre);
							if (!(strlen(tnombre)<=20))
									printf(" LA CADENA DEBE SER MENOR A 20 CARACTERES: ");
						} while (!(strlen(tnombre)<=20));
						BloqMayus(tnombre);
						printf  (" \n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que la ciudad no excede la cantidad de 15 caracteres*/
					void ingciu(char *tciudad ) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tciudad);
							if (!(strlen(tciudad)<=15))
								printf(" DEBE INGRESAR UN NOMBRE MENOR A 15 CARACTERES: ");
						} while (!(strlen(tciudad)<=15));
						BloqMayus(tciudad);
						printf  (" \n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que la direccion no excede la cantidad de 40 caracteres*/
					 void ingdir(char *tdir) {
						do{
							fflush(stdin);
							scanf (" %[^\n]s",&*tdir);
							if (!(strlen(tdir)<=40))
								printf(" DEBE INGRESAR UNA DIRECCION MENOR A 40 CARACTERES: ");
						} while (!(strlen(tdir)<=40));
						BloqMayus(tdir);
						printf("\n\n");
						fflush(stdin);
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/* funcion para validar que la cedula introducida sea valida */
					void ingnum(long int *numero){
						char copia[10];
						int valn;

						do {

							scanf("%s",&copia);
							valn=validar_num(copia);
							*numero=atoi(copia);

							if((*numero==0)||(valn!=0)||(*numero>=maxlongint)){
								printf("\n DEBE INTRODUCIR UN NUMERO VALIDO [ MAYOR A CERO (0) ]: ");
							}
						}while ((*numero==0)||(valn!=0)||(*numero>=maxlongint));
						fflush(stdin);
						*numero=atoi(copia);

					 }

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				/*funcion para mostrar toda la lista de personas*/
		   			void mostrartodo(Personas *per){
					Personas *tper = per;
					for ( ; per; per=per->prox) {
							printf("--------------------------\n");
							printf(" NOMBRE Y APELLIDO: %s\n CEDULA: %i\n FECHA DE NAC: %i/%i/%i \n CIUDAD: %s\n DIRECCION: %s\n", per->nombre_apellido, per->cedula, per->fechas.dia, per->fechas.mes, per->fechas.anio, per->ciudad, per->direccion );
							printf("--------------------------\n");

						}
			  	}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para modificar persona*/
		  			void modificarpersona (Personas **per) {
					int valn, opmod, tanio, tmes, tdia;
					long int copiacedula;
					Personas *tper = *per;
					bool verif=false;
					printf(" INGRESE LA CEDULA DE LA PERSONA A MODIFICAR: ");
					ingnum(&copiacedula);
					tper = buscarpersona(*per, copiacedula, tper->nombre_apellido);
					/*buscarpersona buscara en la lista *per, la cedula de persona
					que se desea modificar y delvolvera un apuntador en donde se encontro la persona,
					por lo tanto tper estara situado en el nodo de la persona que se desea modiciar*/
					if (tper) {
						mostrardatospersona(tper);
						system("pause");
					} else printf("\n LA CEDULA NO SE ENCUENTRA EN EL SISTEMA \n");
						if (tper) {
							do {
								system("cls");
								printf("\n QUE CAMPO DESEA MODIFICAR?");
								printf("\n 1- NOMBRE Y APELLIDO \n 2- FECHA DE NACIMIENTO \n 3- CIUDAD \n 4- DIRECCION \n\n 0- VOLVER \n\n");
								fflush(stdin);
								introduciropcion(&opmod);
								system("cls");
								switch (opmod) {
									case 0:
									break;
									//Modificar Nombre y Apellido
									case 1:
											printf("\n\n INTRODUZCA EL NUEVO NOMBRE Y APELLIDO: ");
											ingnombre(tper->nombre_apellido);
											printf  ("\n");
											fflush(stdin);
									break;
									//Modificar fecha de nacimiento
									case 2:
											printf ("\n\n INTRODUZCA LA NUEVA FECHA DE NACIMIENTO: \n\n");
											ingfecha(&tper->fechas.anio, &tper->fechas.mes, &tper->fechas.dia);
											printf  (" \n");
											fflush(stdin);
									break;
									//Modificar Ciudad
									case 3:
											printf("\n\n INTRODUZCA LA NUEVA CIUDAD: ");
											ingciu(tper->ciudad);
											fflush(stdin);
									break;
									//Modificar Direccion
									case 4:
											printf("\n\n INTRODUZCA LA NUEVA DIRECCION: ");
											ingdir(tper->direccion);
											fflush(stdin);
									break;
									default: printf(" DEBE ELEGIR UNA OPCION VALIDA \n");
											sleep(2);
									}
								} while (opmod!=0);
							}
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar que la opcion ingresada por el usuario es mayor que 1 y no contiene letras*/
					void introduciropcion(int *opcion) {
						char copia[2];
						int valn;
						fflush(stdin);
							do{
								printf("\n INTRODUZCA NUMERO DE OPCION -> ");
								scanf  ("%s",&copia);
								valn=validar_num(copia);
								if ((strlen(copia)>1)||(valn!=0))
									printf("\n DEBE INGRESAR UN NUMERO \n ");
							} while ((strlen(copia)>1)||(valn!=0));
							*opcion=atoi(copia);
							fflush(stdin);
			   		}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion que buscara ya sea por cedula o nombre a una persona,en caso de que cedula==0, significa que la persona desea buscar
				por nombre, de lo contrario se busca por cedula*/
					Personas *buscarpersona(Personas *per, long int cedula, char nombre[]) {
						Personas *tper = per;
							for ( ; tper ; tper=tper->prox) {
								if (cedula == 0) {
									if (strcmp(tper->nombre_apellido, nombre)==0) return tper; //Se encontro usuario con el mismo nombre
								} else {if (tper->cedula == cedula)  return tper;	//Se encontro usuario con la misma cedula )
								   	}
					   }
						 return NULL;
					 }

			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina que dada una persona muestra todos us datos*/
					void mostrardatospersona(Personas *per){

						 if (per==NULL) {
							 printf(" PERSONA NO ENCONTRADA EN EL SISTEMA \n");
						 	} else {
								 system("cls");
								 printf("\n PERSONA ENCONTRADA EN EL SISTEMA \n");
								 printf("--------------------------------------------------------------------------\n");
								 printf (" LOS DATOS DE LAS PERSONAS SON: ");
								 printf  (" \n \n");
								 printf (" \t NOMBRE Y APELLIDO: %s  \n",per->nombre_apellido);
								 printf (" \t CEDULA: %li \n",per->cedula);
								 printf (" \t FECHA DE NACIMIENTO: %d/%d/%d \n",per->fechas.dia,per->fechas.mes,per->fechas.anio);
								 printf (" \t CIUDAD: %s \n",per->ciudad);
								 printf (" \t DIRECCION: %s \n",per->direccion);
								 printf("--------------------------------------------------------------------------\n\n");
							}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para eliminar una persona, dada la lista y la cedula*/
					void Eliminarpersona(Personas **per, int cedula){
						if (*per){
							if ((*per)->cedula==cedula){
								if ((*per)->aba) {
								eliminartodoenvio(per);}
								struct personas *aux=(*per);
								(*per)=(*per)->prox;
								delete (aux);
							}
							else
							{
								Eliminarpersona(&(*per)->prox,cedula);
							}
						}
						else
							printf("\n NO EXISTE NINGUNA PERSONA EN EL SISTEMA \n\n");
					}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para agregar persona*/
					void agregarpersona(Personas **per) {
						Personas *tper;
						tper = new Personas;

						do {
							printf (" INTRODUZCA LA CEDULA: ");
							ingnum(&tper->cedula);
							fflush(stdin);
							if (buscarpersona(*per, tper->cedula, tper->nombre_apellido) != NULL) {//Se valida que la cedula sea unica
								printf("\n LA CEDULA INTRODUCIDA YA SE ENCUENTRA EN EL SISTEMA ");
								printf("\n\n");
							}
						}	while (buscarpersona(*per, tper->cedula, tper->nombre_apellido) != NULL);

						printf ("\n INTRODUZCA EL NOMBRE Y APELLIDO [20 CARACTERES]: ");
						ingnombre(tper->nombre_apellido);
						printf (" INTRODUZCA LA FECHA DE NACIMIENTO:  \n");
						ingfecha(&tper->fechas.anio, &tper->fechas.mes, &tper->fechas.dia);
						printf (" INTRODUZCA SU CIUDAD [15 CARACTERES]: ");
						ingciu(tper->ciudad);
						printf (" INTRODUZCA SU DIRECCION [40 CARACTERES]: ");
						ingdir(tper->direccion);
						tper->aba = NULL;
						tper->prox = NULL;
						//printf(" %i -- %s -- %i/%i/%i -- %s -- %s\n", tper->cedula, tper->nombre_apellido, tper->fechas.dia, tper->fechas.mes, tper->fechas.anio, tper->ciudad, tper->direccion);
						system("pause");
						if (per==NULL) {
							*per = tper;
						 }
						else {
							tper->prox = *per;
							*per = tper;
						}

					}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar el tipo de empresa*/
					void ingtipo(int *tipo){
					char *copiatipo;
					int valn;
					bool ver = false;
						do {
							fflush(stdin);
							scanf ("%s",&*copiatipo);
							valn=validar_num(copiatipo);
							if ((strlen(copiatipo)<1)||(valn!=0)) {
							}	else if ((atoi(copiatipo)>0) && (atoi(copiatipo)<4)){
							*tipo=atoi(copiatipo);
							ver = true;
							}
							if (ver==false)
								printf(" \n OPCION INVALIDA, INGRESE DE NUEVO -> ");
						} while (ver == false);
						fflush(stdin);
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para validar que el numero de telefono sea solo numeros y no exceda los 12 caracteres*/
					void ingtel(char *tlf) {
						int valn;
							do {
								fflush(stdin);
								scanf  ("%s",&*tlf);
								valn=validar_num(tlf);
								if ((strlen(tlf)>12)||(valn!=0))
									printf(" DEBE INGRESAR UN NUMERO DE TELEFONO ADECUADO [ 1 - 12 DIGITOS ]: ");
							} while ((strlen(tlf)>12)||(valn!=0));
							fflush(stdin);
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para validar el codigo, que no poseea letras y no exceda la cantidad de digitos de un numero entero*/
				  	void ingcodigo(int *codigo){
				  		char copia[5];
						int valn;
							do{
								scanf("%s",&copia);
								valn=validar_num(copia);
								*codigo=atoi(copia);
								if((*codigo>=maxint)||(*codigo==0)||(valn!=0)){
									printf("\n EL NUMERO INGRESADO NO ES VALIDO (INGRESE OTRO): ");
								}
							}while ((*codigo>=maxint)||(*codigo==0)||(valn!=0));
							fflush(stdin);
							*codigo=atoi(copia);
				   }
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion que buscara ya sea por codigo, nombre o tipo a una empresa,en caso de que codigo==0 y tipo==0, significa que la persona desea buscar
				por nombre, si codigo!=0 buscara por codigo y si tipo!=0 buscara por tipo */
					Empresas *buscarempresa(Empresas *emp, int codigo, char nombre[], int tipo) {
						Empresas *temp = emp;
						for ( ; temp ; temp=temp->prox) {
							if ((codigo == 0) && (tipo == 0)) {
								if (strcmp(temp->nombreEmp, nombre)==0) return temp; //Se encontro una empresa con el mismo nombre
							} else if (tipo == 0){
								if (temp->codigoEmp == codigo)  return temp;	//Se encontro una empresa con el mismo codigo
							} else if (codigo == 0){
							if (temp->tipo == tipo)  return temp;	//Se encontro una empresa con el mismo tipo
							} //Buscar por tipo nos ayudara a saber si existe por lo menos una empresa de ese tipo
					      }
					      return NULL;
				  }

				 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para agregar empresa*/
					void agregarempresa(Empresas **emp) {
						Empresas *temp;
						temp = new Empresas;
						fflush(stdin);

							do{
								printf(" INTRODUZCA EL CODIGO DE LA EMPRESA : ");
								ingcodigo(&temp->codigoEmp);
								if (buscarempresa(*emp, temp->codigoEmp, temp->nombreEmp, 0) != NULL) {//Se valida que el codigo de la empresa sea unico
									printf("\n EL CODIGO INTRODUCIDO YA SE ENCUENTRA EN EL SISTEMA \n");
									sleep(1); printf("\n\n");
								}
							}	while (buscarempresa(*emp, temp->codigoEmp, temp->nombreEmp, 0) != NULL);
							printf("\n");
							printf (" INTRODUZCA EL NOMBRE DE LA EMPRESA [20 CARACTERES]: ");
							ingnombre(temp->nombreEmp);
							printf (" INTRODUZCA EL TIPO DE LA EMPRESA: \n");
							printf(" 1- COMIDAS\n 2- ALIMENTOS\n 3- GENERAL \n ->");
							ingtipo(&temp->tipo);
							printf("\n");
							printf (" INTRODUZCA EL TELEFONO DE LA EMPRESA [12 CARACTERES]: ");
							ingtel(temp->tlf);
							printf("\n");
							printf (" INTRODUZCA LA DIRECCION DE LA EMPRESA [40 CARACTERES]: ");
							ingdir(temp->direccion);
							temp->aba = NULL;
							temp->prox = NULL;
							//printf(" %i -- %s -- %i -- %s -- %s\n\n", temp->codigoEmp , temp->nombreEmp, temp->tipo, temp->tlf, temp->direccion);
							system("pause");
							if (emp==NULL) {
								*emp = temp;
							 }
							else {
								temp->prox = *emp;
								*emp = temp;
							}
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					void mostrartodoemp(Empresas *emp, int tipo){
						Empresas *temp = emp;
						for ( ; emp; emp=emp->prox) {
							if ((tipo==emp->tipo) || (tipo==4)){
								printf("--------------------------\n");
								printf(" CODIGO: %i\n NOMBRE: %s\n TIPO: %i\n TELEFONO: %s\n DIRECCION: %s\n", emp->codigoEmp, emp->nombreEmp, emp->tipo, emp->tlf, emp->direccion);
								printf("--------------------------\n");
							}
						}
					}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*funcion para modificar empresa*/
					void modificarempresa(Empresas **emp){

						Empresas *temp=*emp;
						int opmod,copiaempresa,copiaemtipo;
						char tnombre[20],tdir[40];

						printf(" INTRODUZCA EL CODIGO DE LA EMPRESA A MODIFICAR: ");
						ingcodigo(&copiaempresa);

						temp=buscarempresa(*emp,copiaempresa,temp->nombreEmp, 0);
						/*buscarempresa buscara en la lista *emp, el codigo de la empresa
						que se desea modificar y delvolvera un apuntador en donde se encontro la empresa,
						por lo tanto temp estara situado en el nodo de la empresa que se desea modiciar*/

						if (temp){
							mostrardatosempresa(temp);
							system("pause");
						}
						else {
							printf("\n EL CODIGO NO SE ENCUENTRA EN EL SISTEMA\n");
						}

						if (temp){
								do {
									system("cls");
									printf("\n QUE CAMPO DESEA MODIFICAR?");
									printf("\n 1- NOMBRE  \n 2- TIPO \n 3- TELEFONO \n 4- DIRECCION \n\n 0- VOLVER \n\n");
									fflush(stdin);
									introduciropcion(&opmod);
									system("cls");

								switch (opmod) {
									case 0:
									break;
									//Modificar Nombre empresa
									case 1:
											printf("\n\n INTRODUZCA EL NUEVO NOMBRE DE LA EMPRESA: ");
											ingnombre(temp->nombreEmp);
											printf  ("\n");
											fflush(stdin);
									break;
									//Modificar tipo de empresa
									case 2:
										printf (" INTRODUZCA EL NUEVO TIPO DE LA EMPRESA: \n");
										printf(" 1- COMIDAS\n 2- ALIMENTOS\n 3- GENERAL \n ->");
										ingtipo(&temp->tipo);
										printf  ("\n");
										fflush(stdin);
									break;
									//Modificar telefono empresa
									case 3:
											printf (" INTRODUZCA EL NUEVO TELEFONO DE LA EMPRESA [12 CARACTERES]: ");
											ingtel(temp->tlf);
											printf("\n");
									break;
									//Modificar Direccion empresa
									case 4:
										printf (" INTRODUZCA LA NUEVA DIRECCION DE LA EMPRESA [40 CARACTERES]: ");
										ingdir(temp->direccion);
									break;
									default: printf(" DEBE INGRESAR UNA OPCION VALIDA ");
											sleep(2);
							}

					} while(opmod!=0);

				  }
			 }

				/////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dada una empresa, muestra todos sus datos*/
				void mostrardatosempresa(Empresas *emp){

					if (emp==NULL){
						printf("\n EMPRESA NO ENCONTRADA EN EL SISTEMA \n");
					}
					else
					{
						printf("\n EMPRESA ENCONTRADA EN EL SISTEMA \n\n");
						printf("--------------------------------------------------------------------------");
						printf ("\n LOS DATOS DE LA EMPRESA SON: ");
						printf  (" \n\n");
					    printf (" \t CODIGO DE LA EMPRESA: %i  \n",emp->codigoEmp);
				      	printf (" \t NOMBRE DE LA EMPRESA: %s \n",emp->nombreEmp);
					  	printf (" \t TIPO DE EMPRESA: %d \n",emp->tipo);
				      	printf (" \t TELEFONO DE LA EMPRESA: %s \n",emp->tlf);
					 	printf (" \t DIRECCION: %s \n",emp->direccion);
				    	printf("--------------------------------------------------------------------------\n\n");
					}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Se elimina toda la lista de productos de una empresa*/
				void eliminartodoprod(Empresas **emp){
					Productos *tprod, *aux;
					tprod = (*emp)->aba;
						while (tprod){
								aux = tprod;
								tprod = tprod->prox;
								delete aux;
						}
						(*emp)->aba = NULL;
				 }

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para eliminar una empresa, dada la lista y el codigo*/
				void Eliminarempresa(Empresas **emp,int codigo, Personas **per){

					if (*emp){
						if((*emp)->codigoEmp==codigo){
						if ((*emp)->aba) eliminartodoprod(emp); //se deben eliminar toda la lista de productos de esa empresa
						struct empresas *aux=(*emp);
						(*emp)=(*emp)->prox;
						delete (aux);
						system("cls");
						printf("\n\tEMPRESA ELIMINADA CON EXITO!!!\n\n");
						Personas *tper = *per;
						Pedidos *ped;
						for (; tper; tper=tper->prox){	//De esta manera eliminamos los pedidos asociados a la empresa eliminada
							ped = tper->aba;
							for (; ped; ped=ped->prox){
								if (ped->codigoEmp == codigo)
								 {
									eliminarenvio(&tper, ped->factura);
								 }

							}
						}
						}
						else
						{
						Eliminarempresa(&(*emp)->prox,codigo, per);
						}
					}
					else
						printf(" LA EMPRESA NO SE ENCUENTRA EN EL SISTEMA \n");
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void prodactivo(bool *act) {
				int valn, activo;
				char copiaactivo[2];
					do {
						do {
							printf("\n 1- SI \n 0- NO \n-> ");
							scanf ("%s",&copiaactivo);
							valn=validar_num(copiaactivo);
							if ((strlen(copiaactivo)<1)||(valn!=0))
								printf(" DEBE INGRESAR UN NUMERO  \n\n");
						} while ((strlen(copiaactivo)<1)||(valn!=0));
						activo=atoi(copiaactivo);
					} while((activo!=1) && (activo!=0));
					if (activo == 1)*act=true;
					else	*act=false;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion para buscar un producto (solo por codigo) dentro de una empresa en especifico*/
				Productos *buscarproductosenempresa(Empresas *emp, int codigo) {
					Productos *tprod;
					if (emp->aba) {
						tprod=emp->aba;
						for ( ; tprod ; tprod=tprod->prox) {
								if (tprod->codigoPrt == codigo)  return tprod;	//Se encontro un producto con el mismo codigo
						}
					}
					tprod = NULL;
					return tprod;
				 }

	 			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Funcion para agregar un nuevo producto
				void agregarproducto(Productos **prod, Empresas **emp, int codigo) {

					Productos *tprod;
					tprod = new Productos;
					Empresas *temp;
					char vacio[2];
					temp = buscarempresa(*emp, codigo, vacio, 0);
					printf(" EMPRESA: %s\n\n", temp->nombreEmp);
					do {
						printf(" INTRODUZCA EL CODIGO DEL PRODUCTO: ");
						ingcodigo(&tprod->codigoPrt);
						printf  (" \n");
						fflush(stdin);
						if (buscarproductosenempresa(temp, tprod->codigoPrt)) printf(" EL CODIGO DEL PRODUCTO YA SE ENCUENTRA REGISTRADO EN ESTA EMPRESA \n\n");
					} while (buscarproductosenempresa(temp, tprod->codigoPrt));

					printf (" INTRODUZCA LA DESCRIPCION DEL PRODUCTO [20 CARACTERES]: ");
					ingnombre(tprod->descripcion);
					printf(" INTRODUZCA EL PRECIO POR UNIDAD: ");
					ingnum(&tprod->precioUd);
					printf  (" \n");
					fflush(stdin);
					printf(" INDIQUE SI EL PRODUCTO ESTA ACTIVO: ");
					prodactivo(&tprod->activo);
					printf("\n");
					tprod->prox = NULL;
					if ((temp->aba)==NULL) {temp->aba = tprod;}
					else {
						Productos *tprod2;
						tprod2 = temp->aba;
						for ( ; tprod2->prox ; tprod2 = tprod2->prox );
						tprod2->prox = tprod;
					}

					printf  (" \n \n");
					system("cls");
					printf("\n\n\tPRODUCTO AGREGADO CON EXITO!!!\n\n");

				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dado un producto, muestra todos sus datos*/
				void mostrardatosprod(Productos *prod){

					system("cls");
					if (prod==NULL){
						printf("\n PRODUCTO NO ENCONTRADO EN EL SISTEMA \n");
					}
					else
					{
						system("cls");
						printf("\n PRODUCTO ENCONTRADO EN EL SISTEMA \n\n");
						printf("--------------------------------------------------------------------------");
						printf ("\n LOS DATOS DEL PRODUCTO SON: ");
						printf  (" \n \n");

						printf (" \t CODIGO DEL PRODUCTO: %i  \n",prod->codigoPrt);
						printf (" \t DESCRIPCION DEL PRODUCTO: %s \n",prod->descripcion);
						printf (" \t PRECIO POR UNIDAD: %li \n",prod->precioUd);
						if (prod->activo==true)
							printf (" \t ACTIVO: SI \n");
						else printf (" \t ACTIVO: NO \n");
						printf("--------------------------------------------------------------------------\n\n");
				 }
			  }

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para modificar un Producto*/
				void modificarproducto(Productos *prod, Personas **per, int codigo) {
				int opmod;
				Personas *tper;
				Pedidos *ped;
				Prodinc *prodinc;

					if (prod) {
							 mostrardatosprod(prod);
							 system("pause");

							do {
								system("cls");
								printf("\n QUE CAMPO DESEA MODIFICAR?");
								printf("\n 1- DESCRIPCION  \n 2- PRECIO \n 3- ACTIVIDAD \n\n 0- VOLVER \n");
								fflush(stdin);
								introduciropcion(&opmod);
								system("cls");
								switch (opmod) {
									case 0:
									break;
									case 1:
											printf("\n DESCRIPCION\n\n");
											printf ("\n INTRODUZCA LA DESCRIPCION DEL PRODUCTO [20 CARACTERES]: ");
											ingnombre(prod->descripcion);
											printf  (" \n");
											fflush(stdin);
									break;
									case 2:
											printf("\n PRECIO\n\n");
											printf("\n INTRODUZCA EL PRECIO POR UNIDAD: ");
											ingnum(&prod->precioUd);
											printf  (" \n");
											fflush(stdin);
											
											tper = *per;
											
											for (; tper; tper=tper->prox){
												ped = tper->aba;
												//se modifica el producto dentro de los pedidos (no entregados) que lo incluyen
												for(; ped; ped=ped->prox){
													if ((ped->codigoEmp == codigo) && (!ped->entregados)){
														prodinc = ped->aba;
															for (; prodinc; prodinc=prodinc->prox){
																if (prodinc->codigoPrt == prod->codigoPrt){
																	prodinc->precio = prod->precioUd;
																	ped->monto_total=PrecioTotal(ped->aba);
																}
															}
													}
												}
											}																						
									break;
									case 3:
											printf("\n ACTIVIDAD\n\n");
											printf("\n INDIQUE SI EL PRODUCTO ESTA ACTIVO:");
											prodactivo(&prod->activo);
									break;
									default:printf(" DEBE INGRESAR UNA OPCION VALIDA ");
											sleep(2);
								}
							} while(opmod!=0);
						} else {printf("\n EL PRODUCTO NO SE ENCUENTRA EN EL SISTEMA \n\n");}
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para eliminar un producto en especifico (por su codigo)*/
				void Eliminarproducto(Empresas **emp, int codigo, Personas **per){

					Empresas *temp;
					temp = *emp;
					Productos *tprod;
					Personas *tper = *per;

						if (temp->aba) {
							tprod=temp->aba;
							if (tprod->codigoPrt == codigo) {		//si el producto a eliminar se encuentra encabezando la lista
								Productos *aux=temp->aba;
								temp->aba = tprod->prox;
								delete aux;
								printf("\n\tPRODUCTO ELIMINADO CON EXITO!!!\n\n");
							} else
									for ( ; tprod ; tprod=tprod->prox) {
										if (tprod->prox->codigoPrt == codigo) { 	//si el producto a eliminar no se encuentra encabezando la lista									
											Productos *aux;
											aux = tprod->prox;
											tprod->prox=tprod->prox->prox;
											delete aux;
											printf("\n\tPRODUCTO ELIMINADO CON EXITO!!!\n\n");
											break;
										}
									}
						}


			    Pedidos *ped;
					for (; tper; tper=tper->prox){
						ped = tper->aba;
						//se elimina el producto dentro de los pedidos que lo incluyen
						for(; ped; ped=ped->prox){

							if (ped->codigoEmp == (*emp)->codigoEmp){
								eliminarprodinc(&ped, codigo);
								ped->monto_total=PrecioTotal(ped->aba);

								if (!ped->aba)
							  	 {
									eliminarenvio(&tper, ped->factura);   //si el envio queda vacio, este se elimina
								 }

							}
						}
					}

			   }

				 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar todos los productos de una empresa en especifico (por codigo)*/
				 void mostrarproductosemp(Empresas *emp, int codigo){
					 Productos *prod;

					 for ( ; emp; emp=emp->prox){
						 if (codigo==emp->codigoEmp){
							 	prod=emp->aba;
								printf("\n LISTA DE PRODUCTOS DE '%s'\n", emp->nombreEmp);
							 	for ( ; prod; prod=prod->prox){
									printf("\n--------------------------------------------------------------------------\n");
			 	 					printf (" \t CODIGO DEL PRODUCTO: %i  \n",prod->codigoPrt);
			 	 					printf (" \t DESCRIPCION DEL PRODUCTO: %s \n",prod->descripcion);
			 	 					printf (" \t PRECIO POR UNIDAD: %li \n",prod->precioUd);
			 	 					if (prod->activo==true)
			 	 						printf (" \t ACTIVO: SI \n");
			 	 					else printf (" \t ACTIVO: NO \n");
			 	 					printf("--------------------------------------------------------------------------\n");
						 }
					 }
				 }
				}

 			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 			 /*Funcion para verificar que exista por lo menos un envio (en general o sobre una empresa en especifico)*/
 			 bool existeenvio(Personas *per, int codigo){

 			 	Personas *tper;
				tper = per;
				Pedidos *tped;
					for ( ; tper ; tper=tper->prox) {
							if ((tper->aba) && (codigo==0)) {	//buscar envio en general
							return true;
							}
							else if ((tper->aba) && (codigo!=0)) {	//buscar envio sobre una empresa en especifico
								tped=tper->aba;
								for (; tped; tped=tped->prox)
									if (tped->codigoEmp == codigo) return true;
							}
					}
					return false;
			  }

 			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*Funcion para buscar un pedido (orden de envio) por su numero de factura, y devuelve la direccion de memoria de el nodo encontrado, de caso contrario NULL*/
			Pedidos *buscarenvios(Personas *per, int factura) {
				
					Personas *tper;
					tper = per;
					Pedidos *tped;
					
					for ( ; tper ; tper=tper->prox) {
							if (tper->aba) {
								tped=tper->aba;
								for ( ; tped ; tped=tped->prox) {
										if (tped->factura == factura) return tped;	//Se encontro un pedido con la misma factura
								}
							}
					}
					tped = NULL;
					return tped;
			 }

			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para buscar un producto incluido (Desde la lista dinamica Prodinc) por su numero codigo, y devuelve la direccion de memoria de el nodo encontrado, de caso contrario NULL*/
				Prodinc *buscarprodinc(Prodinc *prodinc, int codigo) {

					for ( ; prodinc ; prodinc=prodinc->prox) {
							if (prodinc->codigoPrt == codigo) return prodinc;	//Se encontro un pedido con la misma factura
					}
					prodinc = NULL;
					return prodinc;
			 }

 			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 			/*Rutina para mostrar todos los productos incluidos de un pedido*/
 			 	void mostrarproductosincluidos (Prodinc *prodinc){

	 			 	printf (" PRODUCTOS EN EL PEDIDO: \n");
						for ( ; prodinc ; prodinc=prodinc->prox) {
						printf ("\n----------------------------------------------------------------------\n");
						printf (" \t CODIGO: ");
						printf ("%i  ",prodinc->codigoPrt);
						printf ("\t CANTIDAD: %d",prodinc->cantidad);
						printf (" \t PRECIO: %.2f $\n",prodinc->precio);
						printf ("----------------------------------------------------------------------\n");
					 	}

				}
			 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para mostrar los datos de un pedido (buscandola por numero de factura)*/
			 void mostrarfactura (Personas *per, int factura){

				 Prodinc *prodinc;
				 Pedidos *ped;
				 Personas *tper;
				 tper = per;

					for ( ; tper ; tper=tper->prox) {

						if (tper->aba) {
							ped=tper->aba;
							for ( ; ped ; ped=ped->prox) {
									if (ped->factura == factura){
										prodinc=ped->aba;
										printf ("\n\t--------------------------------------------------------------------------\n\n");
										printf ("\t                             ORDEN DE ENVIO                             \n\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                  PERSONA                                 \n\n");
										printf ("\t  NOMBRE Y APELLIDO: %s  ", tper->nombre_apellido);
										printf ("\t  \t  \t  CEDULA: %li  \n\n ",tper->cedula);
										printf ("\t  FECHA DE NACIMIENTO: %d/%d/%d ",tper->fechas.dia, tper->fechas.mes, tper->fechas.anio);
										printf ("\t  \t  CIUDAD: %s  \n\n",tper->ciudad);
										printf ("\t  DIRECCION: %s \n\n",tper->direccion);
										printf ("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                  PEDIDO                                  \n\n");
										printf (" \t  \t  \t        NUMERO DE FACTURA: ");
										printf ("%i  \n\n",ped->factura);
										printf (" \t  \t  \t        CODIGO DE LA EMPRESA: ");
										printf ("%i  \n\n",ped->codigoEmp);
										printf ("\t\tFECHA DE EMISION: %d/%d/%d",ped->fechas.dia, ped->fechas.mes, ped->fechas.anio);
										printf (" \t      MONTO TOTAL: %.2f $\n\n", ped->monto_total);
										if (ped->entregados){
										printf (" \t \t \t\t\tENTREGADO: SI \n\n");
										} else { printf (" \t \t \t\t\tENTREGADO: NO \n\n");}
										printf("\t--------------------------------------------------------------------------\n");
										printf ("\t--------------------------------------------------------------------------\n\n");
										printf ("\t                                 PRODUCTOS                               \n\n");
										for ( ; prodinc ; prodinc=prodinc->prox) {
											printf ("\t    CODIGO: ");
											printf ("%i  ",prodinc->codigoPrt);
											printf (" \t \tCANTIDAD: %d",prodinc->cantidad);
											printf (" \t \tPRECIO: %.2f $\n",prodinc->precio);
											printf ("\t--------------------------------------------------------------------------\n\n");
										}
										system("pause");
										break;
									}  ;
									}
							}
					}

					if (ped==NULL){
					 printf("\n EL NUMERO DE FACTURA NO SE ENCUENTRA EN EL SISTEMA ");
					 return;}
			 }

			 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para agregar un producto en un envio especifico*/
			void agregarproductoincluido (Prodinc **prodinc, Empresas *emp){
			int codigo2;
			Productos *prod;

			printf("\n INGRESE EL CODIGO DEL PRODUCTO A AGREGAR: ");
			ingcodigo(&codigo2);

				//Buscamos el producto dentra de la empresa
				prod = buscarproductosenempresa(emp, codigo2);
				//Debemos verificar que el producto que desea agregar el usuario se encuentre dentro de la lista de productos de la empresa elegida
				if ((!prod) || (prod->activo==false)){
					printf("\n EL PRODUCTO NO EXISTE O NO ESTA ACTIVO\n");
					system("pause");
					return;
				};
				Prodinc *x;
				x = buscarprodinc(*prodinc, codigo2);
				if (x){
						printf("\n EL PRODUCTO QUE DESEA INGRESAR, YA ESTA INCLUIDO\n ACTUALMENTE TIENE: %i UNIDAD/ES \n\n ", x->cantidad);
						system("pause");
						return;
				};
				//Al saber que el producto existe y esta activo, creamos el nodo de productos incluidos y lo llenamos
				Prodinc *prodinccopia;
				prodinccopia = new Prodinc;
				prodinccopia->codigoPrt = codigo2;
				printf("\n CANTIDAD: ");
				ingcodigo(&prodinccopia->cantidad);
				prodinccopia->precio = prod->precioUd;
				prodinccopia->prox = NULL;
			    //se agrega el nuevo nodo de detalleproductosincluidos
				if (*prodinc == NULL){	//if el pedido no tiene ningun producto
					*prodinc=prodinccopia;
				} else {				//else se agrega el nuevo producto por cola
						Prodinc *cola;
						cola = *prodinc;
						for ( ; cola->prox; cola=cola->prox);
							cola->prox=prodinccopia;
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para agregar un envio*/
			 void agregarenvio(Personas **per, Empresas *emp){

			 	long int copiacedula;
			 	printf(" QUIEN DESEA HACER EL PEDIDO? (INGRESE LA CEDULA): ");
				ingnum(&copiacedula);
				Personas *tper;
			 	tper = buscarpersona(*per, copiacedula, vacio);
			 	 if (tper==NULL) {
				 	printf("\n LA CEDULA INGRESADA NO SE ENCUENTRA EN EL SISTEMA\n\n");
				 	printf(" REGRESARA AL MENU ANTERIOR\n\n");
				 	system("pause");
				 	return;
				 }

				 int tipo, codigo, codigo2, op, equiv;
				 equiv=2;

				 printf("\n PERSONA: %s\n\n", tper->nombre_apellido );

				do {
					 printf (" INTRODUZCA EL TIPO DE EMPRESA: \n");
					 printf(" 1- COMIDAS\n 2- ALIMENTOS\n 3- GENERAL \n ->");
					 ingtipo(&tipo);

					 	if (buscarempresa(emp, 0, vacio, tipo) == NULL) {
					 		equiv--;
				 			printf("\n NO EXISTE NINGUNA EMPRESA DE ESE TIPO\n TIENE %i INTENTO/S PARA REGRESAR AL MENU\n\n", equiv);
				 			if (equiv==0){
				 				printf("\n REGRESARA AL MENU \n\n");
				 				system("pause");
							  return;}
						 }
			    } while (buscarempresa(emp, 0, vacio, tipo) == NULL);

			    equiv=2;
				printf("\n EMPRESAS DE TIPO %i: \n", tipo);
				mostrartodoemp(emp, tipo);
				Empresas *xemp;
				do {
				 	printf("\n INTRODUZCA EL CODIGO DE LA EMPRESA: ");
				 	ingcodigo(&codigo);
				 	//Buscamos la empresa con el codigo ingresado
				 	xemp = buscarempresa(emp, codigo, vacio, 0);
				 	if (xemp==NULL){
				 		printf("\n EL CODIGO DE LA EMPRESA QUE HA INGRESADO NO SE ENCUENTRA EN EL SISTEMA \n\n");
				 		system("pause");
				 		return;
					 }
				 	if (xemp->tipo!=tipo){
					 		equiv--;
					 		printf("\n EL CODIGO DE EMPRESA QUE HA INGRESADO NO SE ENCUENTRA DENTRO DE LAS EMPRESAS TIPO '%i'\n", tipo);
					 		printf(" TIENE %i INTENTO/S PARA REGRESAR AL MENU\n\n",equiv);
				 			if (equiv==0){
				 				printf("\n REGRESARA AL MENU \n\n");
				 				system("pause");
							  return;}
					}
				} while (xemp->tipo!=tipo);

				    if (xemp->aba==NULL) {
						 	printf("\n LA EMPRESA SELECCIONADA NO TIENE NINGUN PRODUCTO \n\n");
						 	printf(" REGRESARA AL MENU ANTERIOR\n\n");
					 		system("pause");
					 		return;
						 }

				Productos *prod;
				Pedidos *ped;
				ped = new Pedidos;
				ped->entregados = false;
				Prodinc *prodinc;
				prodinc = NULL;
				system("cls");
				do {
						mostrarproductosemp(emp, codigo);
						printf("\n QUE DESEA HACER?\n");
						printf("\n 1- AGREGAR \n");
						if (prodinc) printf(" 0- CONTINUAR PEDIDO ");
						fflush(stdin);
						introduciropcion(&op);
						switch(op){
							case 0: break;
							case 1: system("cls");
									printf("\n\tAGREGAR\n");
									mostrarproductosemp(emp, codigo);
									agregarproductoincluido (&prodinc, xemp);
							break;
							default:
							printf(" DEBE ELEGIR UNA OPCION VALIDA\n");
						}
				   system("cls");
				} while ((op!=0)||(prodinc==NULL));
				//una vez ingresados todos los productos del pedido, se incluyen (detalles de productos incluidos) al pedido (por "aba")
				//y se llena el pedido

				printf("\n\tCONTINUAR PEDIDO\n\n");
				ped->aba=prodinc;
				ped->codigoEmp=codigo;
				ped->prox=NULL;
				printf (" INTRODUZCA LA FECHA :  \n");
				ingfecha(&ped->fechas.anio, &ped->fechas.mes, &ped->fechas.dia);

				 //Recorremos toda la lista de productos del pedido para hallar la suma total
				 ped->monto_total=PrecioTotal(ped->aba);
				do{
					 printf(" INTRODUZCA EL NUMERO DE LA FACTURA: ");
					 ingcodigo(&ped->factura);
					 	 if (buscarenvios(*per, ped->factura)) {
							 printf("\n EL NUMERO DE FACTURA YA SE ENCUENTRA EN EL SISTEMA\n\n");
						 }
			    } while (buscarenvios(*per, ped->factura));
				
				//por ultimo, se le asigna el pedido a la persona
				if (tper->aba){	//if no es el primer envio de la persona
					 ped->prox = tper->aba; //se inserta el nuevo envio por cabeza
				};
				tper->aba = ped; //se actualiza el nuevo puntero cabeza como multilista
				system("cls");
				printf("\n\n\tPEDIDO AGREGADO CON EXITO!!!\n\n");
				system("pause");
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina para cerrar un envio*/
			void cerrarenvio (Personas **per, int copiafactura ){
				Pedidos *ped;
				ped=buscarenvios(*per, copiafactura);

					if (ped==NULL){
						printf("\n NO EXISTE NINGUN PEDIDO CON ESE NUMERO DE FACTURA EN EL SISTEMA\n\n");
						system("pause");
						return;
					}
					if (ped->entregados==true){
						printf("\n EL PEDIDO YA HA SIDO ENTREGADO\n\n");
						system("pause");
						return;
					}
				ped->entregados=true;
				printf("\n PEDIDO '%i' ENTREGADO \n\n", copiafactura);
				system("pause");
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar un producto incluido (especifico) en un pedido, (por su codigo)*/
			void eliminarprodinc (Pedidos **ped, int codigo){

				Prodinc *x;
				x = (*ped)->aba;
				for ( ; x; x=x->prox){

					if (x->codigoPrt == codigo){	//si el producto inc esta de cabeza en la lista
						Prodinc *y;
						y=x;
						x=x->prox;
						delete y;
						(*ped)->aba = x;
						return;
					}
					if (x->prox)	//x->prox debe existir
						if (x->prox->codigoPrt == codigo){ // si no esta de cabeza en la lista
							Prodinc *y;
							y = x->prox;
							x->prox = x->prox->prox;
							delete y;
							return;
						}
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			void Modificarenvio (Personas **per, int copiafactura, Empresas *emp){
				Pedidos *ped;
				Personas *tper;
				int opmod, codigo2;

				ped=buscarenvios(*per, copiafactura);

				//no se puede modificar un pedido ya entregado
				if (ped->entregados==true){
					printf("\n EL PEDIDO QUE DESEA MODIFICAR YA HA SIDO ENTREGADO \n\n");
					system("pause");
					return;
				}

				Prodinc *prodinc;
				prodinc = ped->aba;

				Productos *prod;

				mostrarfactura (*per, copiafactura);

						do {
							system("cls");
							printf("\n QUE CAMPO DESEA MODIFICAR?");
							printf("\n 1- AGREGAR  \n 2- ELIMINAR \n 3- MODIFICAR CANTIDAD \n\n 0- FINALIZAR \n");

									fflush(stdin);
									introduciropcion(&opmod);
									system("cls");

									switch (opmod) {
										case 0:
										break;
										case 1:
												printf("\n AGREGAR\n\n");
												mostrarproductosemp(emp, ped->codigoEmp);
												agregarproductoincluido (&prodinc, buscarempresa(emp,ped->codigoEmp, vacio, 0));
										break;
										case 2:
												printf("\n ELIMINAR\n\n");
												
											//	if (prodinc->prox==NULL){
											//		printf(" NO PUEDES ELIMINAR EL ULTIMO PRODUCTO DE ESTE ENVIO\n PUEDE ELIMINAR EL ENVIO EN EL MENU (3.5- ENVIOS) \n\n");
											//		system("pause");
											//		break;
											//	}
												
												mostrarproductosincluidos (ped->aba);
												printf("\n INGRESE EL CODIGO DEL PRODUCTO A ELIMINAR: ");
												ingcodigo(&codigo2);
												if (!(buscarprodinc(prodinc, codigo2))){
													printf("\n NO SE ENCUENTRA NINGUN PRODUCTO CON ESE CODIGO EN SU PEDIDO\n\n");
													system("pause");
													break;
												}
												
												if (prodinc->prox==NULL){
													tper = *per;
													
													printf("\n EL PRODUCTO QUE DESEA ELIMINAR ES EL ULTIMO EN ESTE ENVIO, SE ELIMINARA EL ENVIO \n\n");
													system("pause");
													
													for (; tper; tper=tper->prox)
														eliminarenvio(&tper, copiafactura);				
													
													system("cls");	
													printf("\n\t PRODUCTO Y ENVIO ELIMINADO CON EXITO!!!\n\n");	
													system("pause");
													
													return;
																							
												}
												
												eliminarprodinc(&ped, codigo2);
												prodinc=ped->aba;
												system("cls");
												printf("\n\tPRODUCTO ELIMINADO DEL PEDIDO CON EXITO!!!\n\n");
												system("pause");
										break;
										case 3:
												printf("\n MODIFICAR CANTIDAD\n\n");
												Prodinc *x;
												mostrarproductosincluidos (ped->aba);
												printf("\n INGRESE EL CODIGO DEL PRODUCTO A MODIFICAR: ");
												ingcodigo(&codigo2);
												x = buscarprodinc(prodinc, codigo2);
												if (x==NULL){
													printf("\n NO SE ENCUENTRA NINGUN PRODUCTO CON ESE CODIGO EN SU PEDIDO\n\n");
													system("pause");
													break;
												}
												prod = buscarproductosenempresa(buscarempresa(emp, ped->codigoEmp, vacio, 0), codigo2);
												printf("\n INGRESE LA NUEVA CANTIDAD DE EL PRODUCTO: ");
												ingcodigo(&x->cantidad);
												//x->precio = (prod->precioUd * x->cantidad);
												x->precio = prod->precioUd;
												system("cls");
												printf("\n\tCANTIDAD MODIFICADA CON EXITO!!! \n\n");
												system("pause");
										break;
										default: printf(" DEBE INGRESAR UNA OPCION VALIDA ");
												sleep(2);
									}

						} while(opmod!=0);

					//actualizamos el monto total del pedido
					ped->monto_total=PrecioTotal(ped->aba);

					printf("\n\t ENVIO MODIFICADO CON EXITO!!!\n\n");
					system("pause");

				}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar todos los productos incluidos de un envio*/
			void eliminartodoprodinc(Pedidos **ped){
				Prodinc *prodinc, *aux;
				prodinc = (*ped)->aba;

					while (prodinc){
							aux = prodinc;
							prodinc = prodinc->prox;
							delete aux;
					}
				(*ped)->aba = NULL;
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar todos los envios realizados por una persona*/
			void eliminartodoenvio(Personas **per){
				Pedidos *ped, *aux;
				ped = (*per)->aba;

					while (ped){
							eliminartodoprodinc(&ped);
							aux = ped;
							ped = ped->prox;
							delete aux;
					}
				(*per)->aba = NULL;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion para eliminar un envio en especifico (por su factura)*/
			void eliminarenvio(Personas **per, int factura){

				Pedidos *xped;
				Personas *xper = *per;
				xped = xper->aba;

				for ( ; xped; xped=xped->prox){
					if (xped->factura == factura){ //si el envio esta en cabeza
						Pedidos *yped;
						eliminartodoprodinc(&xped);
						yped=xped;
						xped=xped->prox;
						delete yped;
						(*per)->aba = xped;
						return;
					}
					if (xped->prox)
						if (xped->prox->factura == factura){ // si el envio no esta en cabeza
							Pedidos *yped;
							yped = xped->prox;
							eliminartodoprodinc(&yped);
							xped->prox = xped->prox->prox;
							delete yped;
							return;
						}
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion auxiliar para eliminar un envio, donde se verifican los dartos ingresados antes de eliminar el envio requerido*/
			void eliminarenvioaux(Personas **per){

					int copiacod, copiafactura;
					long int copiacedula;

					printf(" INGRESE EL NUMERO DE FACTURA: ");
					ingcodigo(&copiafactura);
					printf("\n");
					printf(" INGRESE LA CEDULA DE LA PERSONA QUE REALIZO EL ENVIO: ");
					ingnum(&copiacedula);
					printf("\n");
					printf(" INGRESE EL CODIGO DE LA EMPRESA RELACIONADA CON EL ENVIO: ");
					ingcodigo(&copiacod);
					printf("\n");

					Personas *xper;

					xper = buscarpersona(*per, copiacedula, vacio);

					if (xper==NULL){
						printf("\n LA CEDULA INGRESADA NO SE ENCUENTRA EN EL SISTEMA\n\n");
						system("pause");
						return;
					}

					Pedidos *ped, *xped;
					ped = xper->aba;
					xped = xper->aba;

					for ( ; xped ; xped=xped->prox) {
						if ((xped->codigoEmp==copiacod)&&(xped->factura==copiafactura)) {
							break;
						}
					}

					if (xped==NULL){
						printf("\n LA PERSONA INDICADA NO HA REALIZADO UN ENVIO DONDE COINCIDAN EL CODIGO DE LA EMPRESA Y/O FACTURA INDICADA\n\n");
						system("pause");
						return;
					}

					eliminarenvio(&xper, copiafactura);
					system("cls");
					printf("\n ENVIO ELIMINADO CON EXITO!!!\n\n");
					system("pause");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				void Datosemp(int codigo, Personas *per, int *entt, int *noentt, int *clientest, float *ingtotalt, float *promgastadot, int *clientesverift){

						Personas *tper;
						tper = per;
						Pedidos *ped;

						int ent, noent, clientes, clientesverif;
						ent = 0;
						noent = 0;
						clientes = 0;
						clientesverif = 0;

						long int cedula, cedula2;
						cedula = 0;
						cedula2 = 0;

						float ingtotal, promgastado;
						ingtotal = 0;
						promgastado = 0;

						for (; tper; tper=tper->prox){

							ped = tper->aba;

							for ( ; ped; ped=ped->prox){

								if (ped->codigoEmp == codigo){

									if (ped->entregados){
										ent++;
										ingtotal+=ped->monto_total;

											if (cedula2 != tper->cedula){	//necesitamos un contador de clientes verificados
											clientesverif++;				//donde solo cuenten clientes con minimo 1 pedido entregado
											cedula2 = per->cedula;
											}
									}else {
										noent++;
									}

									if (cedula != tper->cedula){
									clientes++;

									}
									// de esta manera solo contamos una vez al cliente
									cedula = tper->cedula;

								}
							}
						}
					if (clientesverif !=0)
					promgastado = ingtotal/clientesverif;
					
					printf(" PEDIDOS ENTREGADOS: %i - PEDIDOS NO ENTREGADOS: %i - CLIENTES ATENDIDOS: %i - INGRESO TOTAL VENDIDO: %.2f$ - PROMEDIO DE GASTO POR CLIENTE: %.2f$ \n\n", ent, noent, clientes, ingtotal, promgastado);

							*entt += ent;
							*noentt += noent;
							*clientest += clientes;
							*ingtotalt += ingtotal;
							*clientesverift += clientesverif;

					}
					
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para mostrar informacion de todas las empresas (4.1.1)*/
					void infodetodaslasemp(Empresas *emp, Personas *per){
						
						int ent, noent, clientes, clientesverif;
						ent = 0; noent = 0; clientes = 0; clientesverif = 0;
						float ingtotal, promgastado;
						ingtotal = 0; promgastado = 0;
						Empresas *temp;
						temp = emp;
							for ( ;temp;temp=temp->prox){
								printf("---------------------------------------------------------------------\n\n");
								printf(" %s:  ", temp->nombreEmp);
								Datosemp(temp->codigoEmp, per, &ent, &noent, &clientes, &ingtotal, &promgastado, &clientesverif);
							}
							if (clientesverif != 0)
							promgastado = ingtotal/clientesverif;
							
							printf("---------------------------------------------------------------------");
							printf("---------------------------------------------------------------------\n\n");

							printf(" | TOTAL:  PEDIDOS ENTREGADOS: %i | - | PEDIDOS NO ENTREGADOS: %i | - | CLIENTES ATENDIDOS: %i | - | INGRESO TOTAL VENDIDO: %.2f$ | - | PROMEDIO DE GASTO POR CLIENTE: %.2f$ | \n\n", ent, noent, clientes, ingtotal, promgastado);
					
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para contar el total de ventas de una empresa*/
					int totalventas(Personas *per,int codigo){

						Personas *tper = per;
						Pedidos *ped;
						int total = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
											if (ped->entregados) total++;
										}
									}
							}
						return total;
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para contar el ingreso total vendido entregado o no entregado*/
					float totaling(Personas *per,int codigo, int i){
						// i == 1 -> total vendido entregado
						// i == 2 -> total vendido no entregado

						Personas *tper = per;
						Pedidos *ped;
						float total = 0;
						float totalno = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
											if (ped->entregados) total += ped->monto_total;
											if (!ped->entregados) totalno += ped->monto_total;
										}
								 }
							}
						if (i==1){
					 	return total;
						} else {
						return totalno;
						}
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Funcion para conocer el promedio de cantidad de productos por factura*/
					float promedioproducto(Personas *per,int codigo){

						Personas *tper = per;
						Pedidos *ped;
						Prodinc *prodinc;
						int productos = 0;
						int pedidos = 0;

							for ( ; tper; tper=tper->prox){
									ped = tper->aba;
									for ( ; ped; ped=ped->prox){
										if (ped->codigoEmp==codigo){
												pedidos++;
												prodinc = ped->aba;
												for ( ; prodinc; prodinc=prodinc->prox) productos += prodinc->cantidad;
										}
								 }
							}
						return (productos/pedidos);
					}
					
					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina swap */
					void swap(long int* a, long int* b){
						int c = *a;
						*a = *b;
						*b = c;
					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina del metodo de ordenamiento burbuja*/
					void BurbujaEnteros(long int* const arrayInt, int nroElementosInt){
						int contadorDeIntercambios;
						for (int i = 0; i < nroElementosInt - 1; i++)
						{
							contadorDeIntercambios = 0;
							for (int j = 0; j < nroElementosInt - 1; j++)
								if (arrayInt[j] < arrayInt[j + 1])
								{
									contadorDeIntercambios++;
									swap(arrayInt + j, arrayInt + j + 1);
								}
							if (contadorDeIntercambios == 0)
								break;
						}

					}

					//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina que dada una empresa muestra informacion de ella y sus clientes*/
					void infodeunaemp(Empresas *emp, Personas *per){

						int consulta;
						Personas *tper = per;

						Personas *xper;
						Pedidos *xped;
						Prodinc *xprodinc;

						printf("\n COMO DESEA ORDENAR LOS CLIENTES?\n");
						printf(" 1- CEDULA\n 2- CANTIDAD DE PEDIDOS \n");

						do {
							fflush(stdin);
							introduciropcion(&consulta);
						} while(consulta!=1 && consulta!=2);

						system("cls");

						printf("\n\t INFORMACION DE UNA EMPRESA\n");

						printf("\n EMPRESA:\n\n NOMBRE: %s \n", emp->nombreEmp);
						printf(" CANTIDAD TOTAL DE VENTAS: %i - INGRESO TOTAL VENDIDO: %.2f$ - TOTAL DE INGRESO NO ENTREGADO: %.2f$ - PROMEDIO DE CANTIDAD DE PRODUCTOS POR FACTURA: %.2f \n\n", totalventas(per,emp->codigoEmp), totaling(per, emp->codigoEmp, 1), totaling(per, emp->codigoEmp, 2), promedioproducto(per, emp->codigoEmp));

						printf("---------------------------------------------------------------------\n");
						printf("---------------------------------------------------------------------\n\n");

						int a = 0;
						tper = per;
						for (; tper ; tper=tper->prox) a++;
						long int array[a+1];
						long int copia[a+1];

						tper = per;
						switch (consulta){
							case 1:	//Por CEDULA
								//llenamos el arreglo con las cedulas, y las ordenamos por burbuja
								for (int x=0; tper; tper=tper->prox, x++) array[x] = tper->cedula;
								BurbujaEnteros(array, a);

							break;
							case 2: //por cantidad de pedidos (Entregados como no entregados)
								//llenamos el arreglo con la cantidad de pedidos de cada persona, y las ordenamos por burbuja
								for (int x=0; tper; tper=tper->prox, x++){
									int cped = 0;
									xped = tper->aba;
									for (; xped; xped=xped->prox)
										if (xped->codigoEmp == emp->codigoEmp) cped++;
									array[x] = cped;
									copia[x] = cped; //con este arreglo copia, podremos mostrar la cantidad de pedidos de cada persona
									
								}
								BurbujaEnteros(array, a);
								BurbujaEnteros(copia, a);

								//Buscamos la persona con la misma cantidad de pedidos
								for (int x=0 ; x<a ; x++){
									tper = per;

									for (; tper; tper = tper->prox){
										bool repe = false;
										long int i = 0;
										int cped=0;
										xped = tper->aba;

										for (; xped; xped=xped->prox)
											if (xped->codigoEmp == emp->codigoEmp) cped++;

										//Verificamos que la persona encontrada no este repetida (en caso que dos o mas personas tengan la misma cantidad de pedidos)
										if (x==0){
											if (cped == array[x]){
											i = tper->cedula;
											array[x] = i;
											break;
											}
										} else{
											for (int y=0 ; y<x ; y++){
												if (array[y] == tper->cedula) {
												repe = true;
												break;
												}
											}
											if ((cped == array[x]) && (!repe)) {
												i = tper->cedula;
												array[x] = i;
												break;
											}
										}
									}
								}
							break;
						}
							printf(" CLIENTE/S:\n\n");
							for (int x=0; x<a; x++){
								float facturado = 0;
								float casifacturado = 0;
								int cprod = 0;
								int casicprod = 0;

								xper=buscarpersona(per, array[x], vacio);
								xped = xper->aba;
									for ( ; xped ; xped=xped->prox){
										if (xped->codigoEmp == emp->codigoEmp){
											if (xped->entregados) facturado += xped->monto_total;
											else casifacturado += xped->monto_total;
											xprodinc=xped->aba;
												for ( ; xprodinc; xprodinc=xprodinc->prox){
													if (xped->entregados) cprod += xprodinc->cantidad;
													else casicprod += xprodinc->cantidad;
												}
										}
									}
								if (facturado != 0) {
									printf(" NOMBRE: %s - CEDULA: %li - TOTAL FACTURADO: ENTREGADO: %.2f$ NO ENTREGADO: %.2f$ - CANTIDAD DE PRODUCTOS: ENTREGADO: %i NO ENTREGADO: %i ",xper->nombre_apellido, xper->cedula, facturado, casifacturado, cprod, casicprod );
									if (consulta == 2) printf("- CANTIDAD DE PEDIDOS: %li", copia[x]);
									printf("\n\n");
								}
							}
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dado la cedula de una persona, muestra los detalles de cada pedido */
					void infocliente(Personas *per){
					Personas *tper=per;
					long int copiacedula;
					Pedidos *ped;
					float totalpercibido=0;
					int prodentregados=0;
					bool existe = false;

					printf(" INGRESE LA CEDULA DEL CLIENTE: ");
					ingnum(&copiacedula);

					tper = buscarpersona(per, copiacedula, vacio);

					if (tper==NULL){
						printf("\n LA CEDULA INGRESADA NO SE ENCUENTRA EN EL SISTEMA\n\n");
						return;
					}
					
					system("cls");

					printf("\n\tDATOS DEL CLIENTE\n\n");
					printf(" NOMBRE: %s - CEDULA: %li",tper->nombre_apellido,tper->cedula);
					ped=tper->aba;

					if (!ped){
						printf("\n\n EL CLIENTE NO TIENE NINGUN PEDIDO \n\n");
						return;
					}

					printf("\n\n\tPEDIDOS ENTREGADOS \n\n");
					for( ;ped;ped=ped->prox){
						int cantidad=0;
						if(ped->entregados){
							existe = true;
							Prodinc *prodinc=ped->aba;
							totalpercibido+=ped->monto_total;
							for(;prodinc;prodinc=prodinc->prox){
								cantidad+=prodinc->cantidad;
								prodentregados+=prodinc->cantidad;
							}
							printf(" ENVIO: %i - ENTREGADO: SI - CANT.DE PRODUCTOS: %i - EMPRESA: %i - MONTO TOTAL: %.2f$ - FECHA: %i/%i/%i \n\n",ped->factura,cantidad,ped->codigoEmp,ped->monto_total,ped->fechas.dia,ped->fechas.mes,ped->fechas.anio);
						}
					}
					if (!existe) printf(" EL CLIENTE NO POSEE PEDIDOS ENTREGADOS\n");

					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n");
					existe = false;

					ped=tper->aba;
					printf("\n\t PEDIDOS NO ENTREGADOS \n\n");
					for( ;ped;ped=ped->prox){
						int cantidad=0;
						if(!ped->entregados){
							existe = true;
							Prodinc *prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){
								cantidad+=prodinc->cantidad;

							}
							printf(" ENVIO: %i - ENTREGADO: NO - CANT.DE PRODUCTOS: %i - EMPRESA: %i - MONTO TOTAL: %.2f$ - FECHA: %i/%i/%i \n\n",ped->factura,cantidad,ped->codigoEmp,ped->monto_total,ped->fechas.dia,ped->fechas.mes,ped->fechas.anio);
						}
					}

					if (!existe) printf("   TODOS LOS PEDIDOS DEL CLIENTE HAN SIDO ENTREGADOS \n\n");

					printf("---------------------------------------------------------------------\n");
					printf("\n | TOTAL DE INGRESO PERCIBIDO: %2.f$ | - | CANT.PRODUCTOS ENTREGADOS: %i | \n",totalpercibido,prodentregados);
					return;
				}

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para calcular el mejor cliente por cantidad total percibida*/
				void mejorclientetotal(Personas *per){
					Personas *tper=per;
					Personas *percopia=NULL;
					Pedidos *ped;
					float mayor,montototal;
					mayor=1;

					for( ;tper;tper=tper->prox){
						ped=tper->aba;
						montototal=0;
						for( ;ped ;ped=ped->prox){
							if (ped->entregados) montototal+=ped->monto_total;
						}
						if (montototal>mayor){
							mayor=montototal;
							percopia=tper;
						}
					}

					printf(" MEJOR CLIENTE POR CANTIDAD TOTAL PERCIBIDA \n");

						if (!percopia){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS ENTREGADOS\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",percopia->nombre_apellido);
					printf("CEDULA: %li\n",percopia->cedula);
					printf("\n");

					return;
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el mejor cliente por la cantidad de productos comprados */
					void mejorclienteproductos (Personas *per){

					Personas *tper=per;
					Pedidos *ped;
					Prodinc *prodinc;
					Personas *copiapersona=NULL;
					int cantidad;
					int mayor=1;

					for(;tper;tper=tper->prox){
						ped=tper->aba;
						cantidad=0;
						for(;ped;ped=ped->prox){
							prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){

								if (ped->entregados) cantidad+=prodinc->cantidad;
							}
						}

						if (cantidad>mayor){
							mayor=cantidad;
							copiapersona=tper;
						}
					}

					printf(" MEJOR CLIENTE POR CANTIDAD DE PRODUCTOS COMPRADOS \n");

						if (!copiapersona){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS ENTREGADOS\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",copiapersona->nombre_apellido);
					printf("CEDULA: %li\n",copiapersona->cedula);
					printf("\n");

					return;
				}

				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el peor cliente por cantidad total NO percibida*/
						void peorclientetotal(Personas *per){
							Personas *tper=per;
							Personas *percopia=NULL;
							Pedidos *ped;
							float mayor,montototal;
							mayor=0;


							for( ;tper;tper=tper->prox){
								ped=tper->aba;
								montototal=0;
								for( ;ped ;ped=ped->prox){
									if (!ped->entregados) montototal+=ped->monto_total;
								}
								if (montototal>mayor){
									mayor=montototal;
									percopia=tper;
								}
							}

							printf(" PEOR CLIENTE POR CANTIDAD TOTAL NO PERCIBIDA \n");

								if (!percopia){
								printf("\n NO EXISTEN CLIENTES CON PEDIDOS NO ENTREGADOS\n\n");
								return;
								}

							printf("\n NOMBRE: %s - ",percopia->nombre_apellido);
							printf("CEDULA: %li\n",percopia->cedula);
							printf("\n");

							return;
						}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					/*Rutina para calcular el peor cliente por la cantidad de productos NO comprados */
					void peorclienteproductos (Personas *per){

					Personas *tper=per;
					Pedidos *ped;
					Prodinc *prodinc;
					Personas *copiapersona=NULL;
					int cantidad;
					int mayor=0;

					for(;tper;tper=tper->prox){
						ped=tper->aba;
						cantidad=0;
						for(;ped;ped=ped->prox){
							prodinc=ped->aba;
							for(;prodinc;prodinc=prodinc->prox){

								if (!ped->entregados) cantidad+=prodinc->cantidad;
							}
						}

						if (cantidad>mayor){
							mayor=cantidad;
							copiapersona=tper;
						}
					}

					printf(" PEOR CLIENTE POR CANTIDAD DE PRODUCTOS NO COMPRADOS \n");

						if (!copiapersona){
						printf("\n NO EXISTEN CLIENTES CON PEDIDOS NO ENTREGADOS\n\n");
						return;
						}

					printf("\n NOMBRE: %s - ",copiapersona->nombre_apellido);
					printf("CEDULA: %li\n",copiapersona->cedula);
					printf("\n");

					return;
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que cuenta la cantidad pedida (Entregada o no dependiendo de su opcion) de un producto en especifico*/
				int contarprod(Personas *per, int codigoPrt, int codigoEmp, int opcion){
					//opcion = 1 cuenta la cantidad comprada de un producto
					//opcion = 2 cuenta la cantidad de un producto no entregado

					Personas *tper = per;
					Pedidos *ped;
					Prodinc *prodinc;
					int cantidad = 0;

					for (; tper; tper=tper->prox){
						ped = tper->aba;

							for (; ped; ped=ped->prox){

								if (opcion == 1)
									if ((ped->codigoEmp == codigoEmp) && (ped->entregados)) {
										prodinc = ped->aba;

										for ( ; prodinc; prodinc=prodinc->prox){
											if (prodinc->codigoPrt == codigoPrt) cantidad += prodinc->cantidad;
										}
									}
								if (opcion == 2)
									if ((ped->codigoEmp == codigoEmp) && (!ped->entregados)) {
										prodinc = ped->aba;

										for ( ; prodinc; prodinc=prodinc->prox){
											if (prodinc->codigoPrt == codigoPrt) cantidad += prodinc->cantidad;
										}
									}
							}
					}

					return cantidad;
				}


				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra los mejores productos (mas vendido y mejor ingreso)*/
				void mejoresprod(Empresas *emp, Personas *per){
					Empresas *temp = emp;
					Productos *prod;
					Productos *xprod=NULL;
					Empresas *xemp;
					int i=0;
					int mayor=0;

					long int j=0;
					long int mayorgenerado=0;
					long int cantidad=0;
					Productos *yprod;
					Empresas *yemp;

					for ( ; temp; temp=temp->prox){
						prod = temp->aba;

						for ( ; prod; prod=prod->prox){

							i = contarprod(per, prod->codigoPrt, temp->codigoEmp, 1);

							j = i*prod->precioUd;

							//actualizamos el producto con mayor cantidad
							if (i>mayor){
							 mayor = i;
							 xprod = prod;
							 xemp = temp;
							}

							//actualizamos el producto con mayor ingreso generado
							if (j>mayorgenerado){
							 cantidad = i;
							 mayorgenerado = j;
							 yprod = prod;
							 yemp = temp;
							}
						}
					}

					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");
					if (xprod == NULL){
					printf(" NINGUN PEDIDO HA SIDO ENTREGADO \n\n");
					return;
					}

					printf(" PRODUCTO MAS VENDIDO \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", xemp->nombreEmp, xprod->descripcion, mayor, (float)xprod->precioUd*(float)mayor);
					printf("---------------------------------------------------------------------\n\n");
					printf(" PRODUCTO CON MEJOR INGRESO \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", yemp->nombreEmp, yprod->descripcion, cantidad , (float)yprod->precioUd*(float)cantidad);
				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra los peores productos (menos vendido y peor ingreso)*/
				void peoresprod(Empresas *emp, Personas *per){

					Empresas *temp = emp;
					Productos *prod;
					Productos *xprod = NULL;
					Empresas *xemp;
					int i=maxint;
					int menor=maxint;

					long int j=maxlongint;
					long int menorgenerado=maxlongint;
					long int cantidad=maxlongint;
					Productos *yprod;
					Empresas *yemp;

					for ( ; temp; temp=temp->prox){
						prod = temp->aba;

						for ( ; prod; prod=prod->prox){

							i = contarprod(per, prod->codigoPrt, temp->codigoEmp, 2);

							if (i!=0){	//evitamos caso borde, donde el producto no se encuentra en ningun pedido (no entregado)

								j = i*prod->precioUd;

								//actualizamos el producto con menor cantidad
								if (i<menor){
								 menor = i;
								 xprod = prod;
								 xemp = temp;
								}

								//actualizamos el producto con menor ingreso generado
								if (j<menorgenerado){
								 cantidad = i;
								 menorgenerado = j;
								 yprod = prod;
								 yemp = temp;
								}
							}
						}
					}

					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");

					if (xprod == NULL){
					printf(" TODOS LOS PEDIDOS DEL CLIENTE HAN SIDO ENTREGADOS\n\n");
					return;
					}

					printf(" PRODUCTO MENOS VENDIDO (NO ENTREGADO)\n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", xemp->nombreEmp, xprod->descripcion, menor, (float)xprod->precioUd*(float)menor);
					printf("---------------------------------------------------------------------\n\n");
					printf(" PRODUCTO CON PEOR INGRESO (NO ENTREGADO) \n\n");
					printf(" EMPRESA: %s - PRODUCTO: %s - CANTIDAD: %i - MONTO: %.2f$  \n\n", yemp->nombreEmp, yprod->descripcion, cantidad , (float)yprod->precioUd*(float)cantidad);

					printf("---------------------------------------------------------------------\n\n");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra informacion de una persona relacionada a una empresa*/
				void infopersona_empresa (Personas *per, Empresas *emp){
					Pedidos *ped;
					Prodinc *prodinc;
					int totalped = 0;
					int totalpedno = 0;
					int totalprod = 0;
					int totalprodno = 0;
					float montoprod = 0;
					float montoprodno = 0;

					ped = per->aba;
					for (; ped; ped=ped->prox){

						if (ped->codigoEmp == emp->codigoEmp){	//solo debemos tomar en cuenta los pedidos de una empresa en especifico

							if (ped->entregados){
								totalped++;
								montoprod += ped->monto_total;
							} else {
								totalpedno++;
								montoprodno += ped->monto_total;
							}

							prodinc=ped->aba;
							for (; prodinc; prodinc=prodinc->prox){

								if (ped->entregados) {
								totalprod += prodinc->cantidad;
								} else {
							 	totalprodno += prodinc->cantidad;
								}
							}
						}
					}

					printf(" EMPRESA: %s - TOTAL DE FACTURAS: ENTREGADAS: %i - NO ENTREGADAS: %i - CANTIDAD DE PRODUCTOS: ENTREGADOS: %i - NO ENTREGADOS: %i - MONTO TOTAL DE FACTURAS: ENTREGADAS: %.2f$ - NO ENTREGADAS: %.2f$ \n\n", emp->nombreEmp, totalped, totalpedno, totalprod, totalprodno, montoprod, montoprodno );
					printf("---------------------------------------------------------------------\n\n");

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que dada una persona muestra el total de: pedidos hechos, productos adquiridos, monto pagado por los productos. Luego
				se muestran la(s) empresa(s) con el total de facturas, las cantidades de productos y monto de cdaa uno*/
				void infodeunaper(Personas *per, Empresas *emp){

					Pedidos *ped;
					Prodinc *prodinc;
					int totalped = 0;
					int totalprod = 0;
					int totalprodno = 0;
					float montoprod = 0;
					float montoprodno = 0;

					mostrardatospersona(per);

					if (!per->aba) {
						printf(" LA PERSONA NO HA REALIZADO NINGUN PEDIDO\n\n");
						return;
					}

					ped = per->aba;

					for( ; ped; ped=ped->prox , totalped++){
						prodinc = ped->aba;

						if (ped->entregados) montoprod += ped->monto_total;
						else montoprodno += ped->monto_total;

						for (; prodinc; prodinc=prodinc->prox){

							if (ped->entregados) {
								totalprod += prodinc->cantidad;
							} else {
							 	totalprodno += prodinc->cantidad;
							}
						}
					}

					printf(" TOTAL DE PEDIDOS HECHOS: %i - TOTAL DE PRODUCTOS: ADQUIRIDOS: %i - NO ADQUIRIDOS: %i - MONTO DE PRODUCTOS: PAGADOS: %.2f$ - NO PAGADOS: %.2f$ \n\n", totalped, totalprod, totalprodno, montoprod, montoprodno );
					printf("---------------------------------------------------------------------\n");
					printf("---------------------------------------------------------------------\n\n");

					ped = per->aba;

					printf(" INFORMACION DE CADA EMPRESA: \n\n");
					printf("---------------------------------------------------------------------\n\n");

					//hacer arreglo con codigos de empresa de los pedidos, de esta manera evitar repetir codigos
					// y hacer el mismo for, pero recorriendo ese arreglo
					int a=0;
					for( ;ped;ped=ped->prox){
						a++;
					}

					ped = per->aba;
					int array[a+1];
					for (int x=0; ped;ped=ped->prox, x++){
						int c=0;

						for(int i=0;i<a;i++){
							if(array[i]==ped->codigoEmp) c++;
						}
						if (c==0) array[x]=ped->codigoEmp;
					}

					for(int x=0 ; x<a; x++){
						if (array[x] != 0)
						infopersona_empresa(per, buscarempresa(emp, array[x], vacio, 0));
					}

				}

				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que muestra la informacion de una personas (y sus pedidos) en relacion a una empresa, de forma detallada */
				void infopersona_empresadetallada(Personas *per, Empresas *emp){
						Pedidos *ped;
						Prodinc *prodinc;
						int totalped = 0;
						int totalprod = 0;
						float montoprod = 0;

						mostrardatospersona(per);

						printf(" EMPRESA: %s \n\n", emp->nombreEmp);

						ped = per->aba;

						for( ; ped; ped=ped->prox ){
							prodinc = ped->aba;

							if (ped->codigoEmp == emp->codigoEmp){
								printf("---------------------------------------------------------------------\n");
								printf("---------------------------------------------------------------------\n\n");
								printf(" NUMERO DE FACTURA: ");	
								printf("%i - MONTO TOTAL: %.2f$ - FECHA: %i/%i/%i - ENTREGADO: ", ped->factura, ped->monto_total, ped->fechas.dia, ped->fechas.mes, ped->fechas.anio );
								if (ped->entregados) printf("SI\n\n");
								else printf("NO\n\n");
								//imprimir datos de cada factura
								totalped++;
								montoprod += ped->monto_total;

								for (; prodinc; prodinc=prodinc->prox){
										printf("---------------------------------------------------------------------\n\n");
										printf("\t CODIGO DEL PRODUCTO: ");
										printf("%i - CANTIDAD: %i - PRECIO: %.2f$ \n\n", prodinc->codigoPrt, prodinc->cantidad, prodinc->precio );
										//imprimir cada detalle de esa factura
										totalprod += prodinc->cantidad;
								}
							}
						}

						if (totalped == 0) {
							printf(" LA PERSONA NO TIENE REGISTRADA NINGUNA FACTURA A NOMBRE DE LA EMPRESA '%s'\n\n", emp->nombreEmp);
							return;
						}
						printf("---------------------------------------------------------------------\n");
						printf("---------------------------------------------------------------------\n\n");
						printf(" | TOTAL DE PEDIDOS HECHOS: %i | - | MONTO TOTAL PEDIDO: %.2f$ | - | TOTAL DE PRODUCTOS: %i | \n\n", totalped, montoprod, totalprod  );

				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que devuleve la direccion de memoria, donde se encuentra el pedido con el monto mas alto*/
				Pedidos *montomasalto(Pedidos *auxped){

					Pedidos *aux=auxped;
					Pedidos *mayor1=NULL;
					int mayor=0;

					for(;aux;aux=aux->prox){
						if(aux->monto_total>mayor){
							mayor=aux->monto_total;
							mayor1=aux;
						}
					}

					return mayor1;
				}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina que devuelve la direccion de memoria, donde se encuentra el pedido con la fecha mas reciente*/
						Pedidos *fechamasreciente(Pedidos *auxped){

							Pedidos *aux=auxped;
							Pedidos *reciente=NULL;
							int anio,mes,dia;
							anio=0;
							mes=0;
							dia=0;

							for(;aux;aux=aux->prox){ //Se recorre cada factura buscando la mas reciente
								if(aux->fechas.anio >anio){
									anio=aux->fechas.anio;
									mes=aux->fechas.mes;
									dia=aux->fechas.dia;
									reciente=aux;
								}
								else{
									if (aux->fechas.anio==anio){
										if(aux->fechas.mes>mes){
											anio=aux->fechas.anio;
											mes=aux->fechas.mes;
											dia=aux->fechas.dia;
											reciente=aux;
										}
										else{
											if(aux->fechas.mes==mes){
												if(aux->fechas.dia>= dia){
													anio=aux->fechas.anio;
													mes=aux->fechas.mes;
													dia=aux->fechas.dia;
													reciente=aux;
												}
											}
										}
									}
								}
							}

							return reciente;

						}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rutina para borrar una lista completa
				void borrarLista(Pedidos **l)
					{
						if(l && *l)
						{
							borrarLista(&((*l)->prox));
							Pedidos *aux = *l;
							*l = NULL;
							delete aux;
						}
					}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				//Rutina para mostrar los numeros de las facturas entregadas y ordenarlo por monto total o por fecha de emision
					void mostrarfacturasentregadas(Personas *per,Pedidos **auxped,Empresas *emp){

						Personas *tper=per;
						Pedidos *xped;
						Pedidos *tped;
						int consulta;
						int a=0;
						Pedidos *tped2=*auxped;
						float montototal=0;

						//Se crea una lista auxiliar (auxped) para guardar las facturas entregadas

						for( ;tper;tper=tper->prox){
							tped=tper->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									xped= new Pedidos;
									xped->factura=tped->factura;
									xped->codigoEmp=tped->codigoEmp;
									xped->fechas.anio=tped->fechas.anio;
									xped->fechas.mes=tped->fechas.mes;
									xped->fechas.dia=tped->fechas.dia;
									xped->entregados=tped->entregados;
									xped->monto_total=tped->monto_total;
									xped->aba=NULL;
									xped->prox=*auxped;
									*auxped=xped;
								}
							}
						}
						if(*auxped==NULL){
							printf(" NO HAY FACTURAS ENTREGADAS EN EL SISTEMA \n");
							return;
						}
							printf(" MEDIANTE QUE OPCION DESEA ORDENAR?\n");
							printf(" 1- MONTO TOTAL\n 2- FECHA DE EMISION \n ");

							do {
								fflush(stdin);
								introduciropcion(&consulta);
								if (consulta!=1 && consulta!=2) {
								printf("\n DEBE INGRESAR UNA DE LAS OPCIONES INDICADAS ");

								}

							} while(consulta!=1 && consulta!=2);

							system("cls");
							switch (consulta){
							//Se ordena por Monto total de mayor a menor
							case 1:
								printf("\n\n\tFACTURAS ENTREGADAS POR MONTO TOTAL \n\n");
								tped2=*auxped;

								for(;tped2;tped2=tped2->prox){
									a++;
									montototal+=tped2->monto_total;
								}

								Pedidos *aux;
								for(int x=0;x<a;x++){
									aux=montomasalto(*auxped);
									if (aux){
										Empresas *em;
										em=buscarempresa(emp,aux->codigoEmp,vacio,0); //Se busca la factura con el monto total mas alto
										printf("---------------------------------------------------------------------\n\n");
										printf(" NUMERO DE FACTURA: ");
										printf("%i - EMPRESA: %i - TIPO DE EMPRESA:%i - MONTO TOTAL: %.2f $ - FECHA: %i/%i/%i\n\n",aux->factura,aux->codigoEmp,em->tipo,aux->monto_total,aux->fechas.dia,aux->fechas.mes,aux->fechas.anio);
										aux->monto_total=0;	//Una vez, impresa la factura, se coloca su monto en 0 para buscar la proxima factura con el monto total mas alto
								}
							}

							break;
							//Se ordena por Fecha de emision la mas reciente primero
							case 2:
								printf("\n\tFACTURAS ENTREGADAS POR FECHA DE EMISION \n\n");
								Pedidos *tped1=*auxped;
								a=0;
								montototal=0;
								for(;tped1;tped1=tped1->prox){
									a++;
									montototal+=tped1->monto_total;
								}

								Pedidos *aux1;
								for(int x=0;x<a;x++){
									aux1=fechamasreciente(*auxped);
									if (aux1){
										Empresas *em;
										em=buscarempresa(emp,aux1->codigoEmp,vacio,0); //Se busca la factura con la fecha reciente
										printf("---------------------------------------------------------------------\n\n");
										printf(" NUMERO DE FACTURA: ");
										printf("%i - EMPRESA: %i - TIPO DE EMPRESA:%i - MONTO TOTAL: %.2f $ - FECHA: %i/%i/%i\n\n",aux1->factura,aux1->codigoEmp,em->tipo,aux1->monto_total,aux1->fechas.dia,aux1->fechas.mes,aux1->fechas.anio);
										aux1->fechas.anio=0; //Se actualiza y se coloca la fecha en 0/0/0 para buscar la proxima factura con la fecha mas reciente
										aux1->fechas.mes=0;
										aux1->fechas.dia=0;
									}

								}

								break;
							}

						printf("---------------------------------------------------------------------\n\n");
						printf("\t | TOTAL DE FACTURAS ENTREGADAS: %i | - | MONTO TOTAL DE FACTURAS ENTREGADAS: %.2f $ |\n\n",a,montototal);
				 		borrarLista(auxped); //Se borra la lista auxiliar

				 	}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para buscar la persona con la mayor cantidad de productos compradas*/
				Personas *personacantidadmasalta(Personas *tper,int *mayor,int *menor){

						Personas *per=tper;
						Pedidos *tped;
						int mayor2=0;
						int montomayor;
						int montomenor;
						int menor2=0;
						Personas *retorno=NULL;
						bool entregado = false; //Un booleano que pasa a verdadero cuando encuentre una persona con algun pedido entregados
												// de esta manera podemos saber cuando solo queden personas con pedidos no entregados

						for(;per;per=per->prox){
							montomayor=0;
							montomenor=0;

							tped=per->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									Prodinc *prod=tped->aba;
									for(;prod;prod=prod->prox){
										montomayor+=prod->cantidad;
									}
								}
								else{
									Prodinc *prod=tped->aba;
									for(;prod;prod=prod->prox){
										montomenor+=prod->cantidad;
									}

								}
							}
							if(montomayor>mayor2){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
								entregado = true;
							} else if (!entregado){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
							}
						}

						*mayor=mayor2;
						*menor=menor2;

						return retorno;

					}
				///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para buscar la persona con el mayor monto total de compras realizadas (todos los pedidos entregados)*/
					Personas *personamontomasalto(Personas *tper,float *mayor,float *menor){

						Personas *per=tper;
						Pedidos *tped;
						float mayor2=0;
						float montomayor;
						float montomenor;
						float menor2=0;
						Personas *retorno=NULL;
						bool entregado = false; //Un booleano que pasa a verdadero cuando encuentre una persona con algun pedido entregados
												// de esta manera podemos saber cuando solo queden personas con pedidos no entregados

						for(;per;per=per->prox){
							montomayor=0;
							montomenor=0;

							tped=per->aba;
							for(;tped;tped=tped->prox){
								if(tped->entregados){
									montomayor+=tped->monto_total;
								}
								else{
									montomenor+=tped->monto_total;
								}
							}
							if(montomayor>mayor2){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
								entregado = true;
							} else if (!entregado){
								mayor2=montomayor;
								menor2=montomenor;
								retorno=per;
							}
						}


						*mayor=mayor2;
						*menor=menor2;

						return retorno;

					}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con mayor monto gastado */
				void mayorpormonto(Personas **auxper, int a){

					float mayor=0;
					float menor=0;
					float montomayor=0;
					float montomenor=0;
					Personas *tper2;

					for(int x=0;x<a;x++){
						tper2=personamontomasalto(*auxper,&mayor,&menor);
						if(tper2){
							printf("---------------------------------------------------------------------\n\n");
							printf(" NOMBRE: %s -- CEDULA: %li -- %.2f $  (-%.2f $)\n\n",tper2->nombre_apellido,tper2->cedula,mayor,menor);
							montomayor+=mayor;
							montomenor+=menor;
							Eliminarpersona(auxper, tper2->cedula); // se debe eliminar cada nodo (que se acaba de usar) de la lista
						}
					}
					printf("---------------------------------------------------------------------\n");
					printf("\n\t | TOTAL: %.2f $ (-%.2f $) | \n\n",montomayor,montomenor);

				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con la mayor cantidad de productos comprados */
				void mayorporcantidad(Personas **auxper, int a){

					Personas *tper2;
					int mayor=0;
					int menor=0;
					int montomayor=0;
					int montomenor=0;

					for(int x=0;x<a;x++){
						tper2=personacantidadmasalta(*auxper,&mayor,&menor);
						if(tper2){
							printf("---------------------------------------------------------------------\n\n");
							printf(" NOMBRE: %s -- CEDULA: %li -- CANTIDAD DE PRODUCTOS: %d  (-%i)\n\n",tper2->nombre_apellido,tper2->cedula,mayor,menor);
							montomayor+=mayor;
							montomenor+=menor;
							Eliminarpersona(auxper, tper2->cedula); // se debe eliminar cada nodo (que se acaba de usar) de la lista
						}
					}
					printf("---------------------------------------------------------------------\n");
					printf("\n\t | TOTAL DE PRODUCTOS: %i (-%i) | \n\n",montomayor,montomenor);
				}

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Rutina para mostrar las personas con mayores montos de compras realizadas y mayor cantidad de productos comprados*/
				void mayoresconsultas(Personas *per, int x){

					Personas *auxper = NULL;
					Personas *tper=per;
					Personas *tper1, *tper2;
					Pedidos *auxped=NULL;
					Pedidos *tped;
					Prodinc *tprodinc, *auxprodinc;
					int a=0;

					//Se crea una lista auxiliar (auxper) para guardar todas las personas

					for(;tper;tper=tper->prox){
						auxped=NULL;
						a++;
						//
						tper1 = new Personas;
						strcpy(tper1->nombre_apellido,tper->nombre_apellido);
						tper1->cedula=tper->cedula;
						//
						if(!tper->aba){
							tper1->aba=NULL;
						}else{
							Pedidos *tped2=tper->aba;
							for(;tped2;tped2=tped2->prox){
								auxprodinc=NULL;
								tped=new Pedidos;
									tped->factura=tped2->factura;
									tped->entregados=tped2->entregados;
									tped->monto_total=tped2->monto_total;

										if (!tped2->aba){
											tped->aba=NULL;
										} else {
											Prodinc *prodinc=tped2->aba;
											for (; prodinc; prodinc=prodinc->prox){
												tprodinc = new Prodinc;
												tprodinc->cantidad=prodinc->cantidad;
												tprodinc->prox=auxprodinc;
												auxprodinc=tprodinc;
											}
											tped->aba=auxprodinc;
										}

									tped->prox=auxped;
									auxped=tped;
							}
							tper1->aba=auxped;
						}
						tper1->prox=auxper;
						auxper=tper1;
					}
					//Si x==1 se mostraran las personas con mayores montos de compras realizadas
					if (x==1) mayorpormonto(&auxper, a);
					else mayorporcantidad(&auxper, a);

				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que devuelve la empresa con mayor ingreso logrado*/
				Empresas *empresamayor(int array[],float *ingreso,int a,Personas *per,Empresas *emp){

					float mayor=0;
					int codigo=0;
					Empresas *temp=NULL;
					int y=0;
					for(int x=0; x<a;x++){
						if(totaling(per,array[x], 1)>mayor){
							mayor=totaling(per,array[x], 1);
							codigo=array[x];
							y=x;
						}
					}
					*ingreso=mayor;
					temp=buscarempresa(emp, codigo, vacio, 0);
					array[y]=0;
					return temp;

				}
          /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				/*Funcion que devuelve la cantidad de productos en facturas entregadas o no entregadas de una empresa en especifico*/
				int cantidad ( Personas *per, int codigo ,int z)
				//z=1 es la cantidad de productos en facturas entregadas
				//z=2 es la cantidad de productos en facturas no entregadas
				 {

				 	 int vendido = 0;
				 	 int novendido=0;
					 Personas *aux;
				 	  aux = per;

				 	   for (; aux; aux = aux->prox) {

				 	   	  Pedidos *ped;
				 	   	  ped = aux->aba;

							 for (; ped; ped = ped->prox) {

							     if ( ( ped->codigoEmp == codigo ) && ( ped->entregados ) && (z==1) ) {
							      	 Prodinc *prod;
							      	  prod = ped->aba;

							      	   for (; prod; prod = prod->prox ) {
				                              vendido+=prod->cantidad;
										  }
								  }
								  else{
								  	 if ( ( ped->codigoEmp == codigo ) && (!ped->entregados ) && (z==2) ) {
							      	 Prodinc *prod;
							      	  prod = ped->aba;

							      	   for (; prod; prod = prod->prox ) {
				                              novendido+=prod->cantidad;
										  }
								  }

								  }
							 }
						}
				 	if(z==1){
				 		return vendido;
					}
					else{
						return novendido;
					}


				 }
			///////////////////////////////////////////////////////////////////////////////////////////////////
			/*Funcion que devuelve la empresa con mayor cantidad de productos vendidos*/
			Empresas *empresacantidad(int array[],int y,Personas *per,Empresas *emp,int *cantidadv){
				int  mayor=0;
				int codigo=0;
				Empresas *temp=NULL;
				int z=0;
					for(int x=0; x<y;x++){
						if(cantidad(per,array[x],1)>mayor){
							mayor=cantidad(per,array[x],1);
							codigo=array[x];
							z=x;
						}
					}
					*cantidadv=mayor;
					temp=buscarempresa(emp, codigo, vacio, 0);
					array[z]=0;
					return temp;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////
			/*Rutina auxiliar para mostrar las empresas con mayores ingresos logrados (4.3.1) y las empresas con mayor cantidad de productos vendidos (4.3.2)*/
				void mayoresempresas(Empresas *emp,Personas *per,int z){
					Empresas *temp=emp;
					int prodentregado = 0;
					int a=0;
					int y=0;
					Empresas *auxemp;
					float ingresototal=0;
					float ingresototalnovendido=0;
					float ingreso=0;
					int cantidadv=0;
					int cantidadno=0;
					int finalvendido=0;
					int finalnovendido=0;
					float montofinal=0;
					for(;temp;temp=temp->prox){
						a++;
					}

					int array[a+1];
					temp=emp;
					for (int x=0; temp; temp=temp->prox, x++) array[x] = temp->codigoEmp;
					y=a;
					if (z==1){ //4.3.1
					for(int x=0; x<a; x++){
						auxemp=empresamayor(array,&ingreso,y,per,emp);
						if(auxemp){
							printf("---------------------------------------------------------------------\n\n");
							printf("  NOMBRE: %s -- TIPO: %i -- INGRESO: %.2f $ ( - %.2f $) -- CANTIDAD: %i \n\n",auxemp->nombreEmp,auxemp->tipo,ingreso,(totaling(per,auxemp->codigoEmp,2)),cantidad(per, auxemp->codigoEmp,1));
							ingresototal+=ingreso;
							prodentregado+=cantidad(per, auxemp->codigoEmp,1);
							ingresototalnovendido+=totaling(per,auxemp->codigoEmp,2);
						}
					}
					printf("---------------------------------------------------------------------\n\n");
					printf(" \t | TOTAL INGRESO:  %.2f $ (-%.2f $) | -- | CANTIDAD TOTAL: %i | \n\n",ingresototal,ingresototalnovendido,prodentregado);
					}
					else{ //4.3.2
						for(int x=0; x<a; x++){
						auxemp=empresacantidad(array,y,per,emp,&cantidadv);
						if(auxemp){
							printf("---------------------------------------------------------------------\n\n");
							printf(" NOMBRE: %s -- TIPO: %i -- CANTIDAD: %i ( - %i) -- MONTO TOTAL: %.2f $ \n\n ",auxemp->nombreEmp,auxemp->tipo,cantidadv,cantidad(per,auxemp->codigoEmp,2),totaling(per,auxemp->codigoEmp,1));
							finalvendido+=cantidadv;
							finalnovendido+=cantidad(per,auxemp->codigoEmp,2);
							montofinal+=totaling(per,auxemp->codigoEmp,1);

						}
					}
					printf("---------------------------------------------------------------------\n\n");
					printf(" \t | CANTIDAD TOTAL:  %i (- %i) | -- | MONTO TOTAL: %.2f $ | \n\n",finalvendido,finalnovendido,montofinal);
					}
				}
