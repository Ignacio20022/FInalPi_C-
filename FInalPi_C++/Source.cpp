#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#include<map>
#include<iomanip>
#include<vector>
#include<algorithm>
using namespace std;


// Declaramos las estructuras para crear los arreglos


struct Categoria {

    int codigo_categoria; //guarda el codigo de la categiora autogenerado
    string descripcion; //guarda la descripcion de la categoria escrita por el ususario

};

struct Prestatario {

    int codigo_prestatario; //guarda el codigo del prestatario autogenerado
    string apellido; //gurada el nombre del prestatario escrito por el usuario
    string nombres; //guarda el apellido del prestatario escrito por el usuario
};

struct Prestamo {

    int codigo_p; //guarda el codigo del prestamo autogenerado
    int codigo_categoria_p; //guarda el mismo codigo de la categoria que eligio el usuario
    string descripcion_categoria_p; //guarda la misma descripcion de la categoria que eligio el ususario
    int codigo_prestatario_p; //guarda el mismo codigo del prestatario que eligio el usuario
    string nombre_p; //guarda el mismo nombre del prestatario que eligio el usuario
    string apellido_p; //guarda el mismo apellido del prestatario que eligio el usuario
    string descripcion_p; //guarda la descripcion del prestamo escrita por el usuario
    bool estado_p; //guarda el estado del prestamo, por determinado es verdadero
    Prestamo* siguiente; //puntero para referenciar a la lista

};

Prestamo* fin = nullptr; //inicia la lista vacia

//Proposito: insertar elementos al fianl de la lista
//Retorno: void
void insertar_final(Prestamo*& fin, Prestamo* n) {
    if (fin == nullptr) //si la lista esta vacia
        fin = n; //el ultimo nodo es el primero
    else {
        Prestamo* aux = fin; //puntero auxiliar
        while (aux->siguiente != nullptr) //se recorre la lista hasta que se llega al ultimo nodo
            aux = aux->siguiente; //se reemplaza aux por el siguiente
        aux->siguiente = n; //cuando sea el ultimo elemento se guarda lo que se paso por 'n' a aux
    }
}

//Proposito: imprimir la lista de prestamos
//Retorno: void
void imprimir_lista(Prestamo*& fin) {
    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //se recorre la lista y se imprime cada elemento
        cout << "\nCodigo: " << aux->codigo_p << ", ";
        cout << "categoria: " << aux->descripcion_categoria_p << ", ";
        cout << "prestatario: " << aux->nombre_p << " " << aux->apellido_p << ", ";
        cout << "descripcion: " << aux->descripcion_p << ", ";
        if (aux->estado_p == true)
            cout << "estado: Activo" << endl;
        else
            cout << "estado: Inactivo" << endl;
    }
}

//Proposito: eliminar elementos de los prestamos
//Retorno: void
void eliminar(Prestamo*& fin, int cod) {

    if (fin != nullptr) { //sigue si hay prestamos
        Prestamo* aux = fin; //crea un nodo auxiliar
        if (fin->codigo_p == cod) { //chequea si el primer elemento es el que se desea eliminar
            fin = fin->siguiente;//reemplaza lo de fin con nullptr
            delete aux; //borra aux
            for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre la lista y decrementa el codigo de cada elemento
                aux->codigo_p--;
            }
        }
        else { //si el elemento a eliminar no es el primero
            while (aux->siguiente != nullptr && aux->siguiente->codigo_p != cod) //reemplaza el auxiliar hasta encontra el codigo en el que le sigue
                aux = aux->siguiente;
            if (aux->siguiente->codigo_p == cod) { //verifica el codigo
                Prestamo* aEliminar = aux->siguiente; //crea aEliminar para aislar el puntero a eliminar
                for (aux->siguiente = aEliminar->siguiente; aux->siguiente != nullptr; aux = aux->siguiente) { //itera a partir del puntero a eliminar y decrementa los codigos en 1
                    aux->siguiente->codigo_p--;
                }
                delete aEliminar; //elimina el puntero
                return;
            }
        }
    }
}

//Proposito: verificar el estado de las categorias
//Retorno: void
void verificar_estado_categoria(Prestamo*& fin, int cod, bool& estado) {
    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
        if (cod == aux->codigo_categoria_p) { //verifica si el codigo seleccionado con los de categoria hasta que son iguales
            if (aux->estado_p == true) { //si el estado es true
                estado = true; //como se paso por referencia cambia estado a true y regresa
                return;
            }
        }
    }
    estado = false; //si no hubo ninguna categoria asociada a un prestamo activo cambia estado a false y regresa
    return;
}

//Proposito: verificar el estado de los prestatarios
//Retorno: void
void verificar_estado_prestatario(Prestamo*& fin, int cod, bool& estado) {
    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
        if (cod == aux->codigo_prestatario_p) { //verifica si el codigo seleccionado con los de prestatarios hasta que son iguales
            if (aux->estado_p == true) { //si el estado es true
                estado = true;
                return;
            }
        }
    }
    estado = false; //si no hubo ninguna categoria asociada a un prestamo activo cambia estado a false y regres
    return;
}

//Proposito: verificar el estado de los prestamos
//Retorno: void
void verificar_estado_prestamo(Prestamo*& fin, int cod, bool& estado) {
    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
        if (cod == aux->codigo_p) { //verifica si el codigo seleccionado con los de prestamos hasta que son iguales
            if (aux->estado_p == true) { //si el estado es true
                estado = true; //como se paso por referencia cambia estado a true y regresa
                return;
            }
        }
    }
    estado = false; //si no hubo ninguna categoria asociada a un prestamo activo cambia estado a false y regres
    return;
}

//Proposito: ordena el vector pasado por referencia
//Retorno: vector
vector<string> orden_alfabetico(vector<string> lista) {
    sort(lista.begin(), lista.end()); //sort ordena lo que recive como parametro, el principio y el final del vector en este caso
    return lista; //retorna el vector ordenado
}

// Declaramos las estructuras para guardar los arreglos y sus dimensiones

const int DIM_FISICA_CATEORIA = 600, DIM_FISICA_PRESTAMO = 600, DIM_FISICA_PRESTATARIO = 600; //constante inicializada en 600 para las estructuras

Categoria categorias[DIM_FISICA_CATEORIA];
int dl_categoria = 0;

Prestatario prestatarios[DIM_FISICA_PRESTATARIO];
int dl_prestatario = 0;

Prestamo prestamos[DIM_FISICA_PRESTAMO];
int dl_prestamo = 0;

//Proposito: parar el programa hasta que el ususario de enter
//Retorno: void
void presione_enter_funciones() {
    cout << "\nPresione ENTER para continuar." << flush;
    cin.get();
    system("cls"); //limpia la consola
}

//Proposito: parar el programa hasta que el ususario de enter
//Retorno: void
void presione_enter_submenus() {
    cout << "\nPresione ENTER para continuar." << flush;
    cin.ignore();
    cin.get();
    system("cls"); //limpia la consola
}
// ***HAY DOS YA QUE DEPENDIENDO DE LO QUE HAYA OCURRIDO ANTES NO FUNCIONABA CORRECTAMENTE***


//FUNCIONES        ******SUBMENU 1*******

/*
Proposito: agregar categorias al struct catecoria1
Retorno: VOID
*/
void  agregar_categoria(Categoria arreglo[], int& dl_categoria) {
    //Inserta elementos(codigo_categoria, descripcion)
    system("cls"); //limpia la consola
    string descripcion; //variable para guarda lo que escriba el usuario temporalmente
    if (dl_categoria < DIM_FISICA_CATEORIA) { //mientras que la dl sea menor que la df se ingresa la categoria y si no esta registrada se agrega junto con el codigo

        cout << "\t***AGREGAR CATEGORIA***" << endl << endl;;
        //se le pide al ususario que ingrese una decipcion
        cout << "Ingrese una descripcion de la categoria(ingrese '0' para cancelar): " << flush;
        getline(cin >> ws, descripcion);
        if (descripcion == "0") { //si se ingreso 0 se cancela
            cout << "Se aborto la operacion" << endl;
            presione_enter_submenus();
            return; //regresa al menu //regresa al menu
        }
        for (int x = 0; x < dl_categoria; x++) { //itera hasta llegar al maximo de dimension logica
            if (arreglo[x].descripcion == descripcion) { // se compara descripcion con todas las descripciones ya agregadas para saber si ya se encuentra o no
                cout << "La categoria que quiere ingresar ya se encuentra registrada y su codigo es: " << arreglo[x].codigo_categoria << endl; //le avisa al ususario que ya se encuaentra agregada y le dice cual es el codigo
                presione_enter_funciones();
                return; //regresa al menu
            }
        }
        arreglo[dl_categoria].descripcion = descripcion; //guarda lo que se ingreso en la posision de logica en descripcion
        arreglo[dl_categoria].codigo_categoria = dl_categoria + 1; //se le asigna automaticamente un codigo a partir de la dimension logica
        cout << "La categoria: " << arreglo[dl_categoria].descripcion << " se agrego correctamente con el codigo: " << arreglo[dl_categoria].codigo_categoria << endl; //avisa al usuario que se agrego correctamente la categoria
        dl_categoria++; // aumenta la dimension logica en 1
        presione_enter_funciones();
        return; //regresa al menu
    }
    //Si la dl es mayor que la df se indica que no se pueden agregar mas categorias
    else {
        cout << "No se puede agregar mas categorias(limite alcanzado)" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
}

/*
Proposito: modificar categorias creadas
Retorno VOID
*/
void modificar_categoria(Categoria arreglo[], int& dl_categoria, Prestamo*& fin) {
    //Muetra las categorias iterando sobre ellas y el usuario elije cual modificar segun el codigo de categoria
vuelta: //punto de regreso en caso de que el codigo ingresado no exista
    system("cls"); //limpia la consola
    int cod_a_mod; //variable para guardar la seleccion del usuario temporalmente
    string descripcion; //varible para almacenar lo que escriba el usuario temporalmente

    cout << "\t***MODIFICAR CATEGORIA***" << endl << endl;

    for (int x = 0; x < dl_categoria; x++) {  //itera en categorias para imprimirlas por pantalla
        cout << "Codigo: " << arreglo[x].codigo_categoria << ", ";
        cout << "descripcion: " << arreglo[x].descripcion << endl;
    }
    cout << "\nIngrese el codigo de la categoria que quiere modificar(para cancelar ingrese '0'): " << flush; //le pide al usuario que ingrese el codigo de una cartegoria para seleccionarla
    cin >> cod_a_mod; //variable que contiene la seleccion del usuario

    if (cod_a_mod == 0) {  //Si el codigo es 0 se aborta la operacion
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    else { //Sino se le pide que ingrese una nueva descripcion para la categoria, y te muestra cual es esa descripcion
        for (int x = 0; x < dl_categoria; x++) { //itera sobre las categorias
            if (arreglo[x].codigo_categoria == cod_a_mod) { //compara los datos en categoria con la seleccion del usuario
                cout << "Ingrese la nueva descripcion de la categoria: " << flush; //se le pide que ingrese una nueva descripcion
                getline(cin >> ws, descripcion);  //guarda lo que escribe el usuario
                for (int i = 0; i < dl_categoria; i++) { //itera sobre las descripciones de las categorias
                    if (arreglo[i].descripcion == descripcion) { //verifica si lo que ingreso el usuario ya se encuentra guardado
                        cout << "Esa descripcion ya esta asignada a la categoria '" << arreglo[i].codigo_categoria << "'"; //se le avisa al usuario que ya se encuentra guardada esa descripcion y le imprime el codigo
                        presione_enter_funciones();
                        return; //regresa al menu
                    }
                }
                cout << "La nueva descripcion de la categoria '" << arreglo[x].codigo_categoria << "' es: " << descripcion << endl; //le avisa al usuario que se modifico correctamente la descripcion
                arreglo[x].descripcion = descripcion; //guarda lo que se ingreso en la posision de logica en descripcion
                for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
                    if (aux->codigo_categoria_p == cod_a_mod) //si coinciden los codigos
                        aux->descripcion_categoria_p = descripcion; //cambia la descripcion de la categoria en los prestamos
                }
                presione_enter_funciones();
                return; //regresa al menu
            }
        }
    }
    //llegado a este punto significa que no ingreso un codigo valido
    cout << "El codigo ingresado no pertenece a ninguna categoria" << endl; //le avisa al usuario que ingreso un codigo inexistente
    presione_enter_submenus();
    goto vuelta; //vuelve a 'vuelta' para intentarlo nuevamente
}

//Porposito: eliminar categorias
//Retorno VOID
void eliminar_categoria(Prestamo*& fin, Categoria arreglo[], int& dl_categoria) {
    //Muetra las categorias iterando sobre ellas y el usuario elije cual eliminar segun el codigo de categoria
    //Se le pedira una confirmacion antes de eliminarlo
vuelta: //punto de regreso en caso de que el codigo ingresado no exista
    system("cls"); //limpia la consola
    int cod_a_del; //variable para guardar la seleccion del usuario
    bool estado;

    cout << "\t***ELIMINAR CATEGORIA***" << endl << endl;;
    for (int x = 0; x < dl_categoria; x++) {   //iteramos en las categorias para imprimirlas
        cout << "Codigo: " << arreglo[x].codigo_categoria << ", ";
        cout << "descripcion: " << arreglo[x].descripcion << endl;
    }
    cout << "\nIngrese el codigo de la categoria que quiera eliminar(para cancelar ingrese '0'): " << flush; //indica al usuario que ingrese un codigo para seleccionar una categoria
    cin >> cod_a_del; //almacena lo que ingreso el usuario

    if (cod_a_del == 0) { //Si es igual a 0 se aborta la operacion
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    else {
        verificar_estado_categoria(fin, cod_a_del, estado);
        if (estado == true) {
            cout << "La categoria no puede eliminarse debido a que tiene asociado prestamos pendientes" << endl;
            presione_enter_submenus();
            goto vuelta; //se dirige a vuelta
        }
        for (int x = 0; x < dl_categoria; x++) { //itera en las categorias
            if (cod_a_del == arreglo[x].codigo_categoria) { //si el codigo elegido es igual a uno en categorias
                for (int i = x; i < dl_categoria - 1; i++) {  //recorre la struct
                    arreglo[i] = arreglo[i + 1];  //reemplaza a lo que se encuentra en 'i' con lo que le sigue y se repite hasta que se llega al liminte de la dimension logica
                    arreglo[i].codigo_categoria--; // reduce en uno el codigo de la categoria
                }
                dl_categoria--; //resta la dimension ya que se elimino un elemento
                cout << "Se elimino la categoria con exito" << endl; //avisa al usuario que se elimino con exito
                presione_enter_submenus();
                return; //regresa al menu
            }
        }
    }
    //en caso de que el programa llegue a este punto significa que no ingreso un codigo valido
    cout << "El codigo ingresado no pertenece a ninguna categoria" << endl;
    presione_enter_submenus();
    goto vuelta; //vuelve a 'vuelta' para intentalo nuevamente
}

//Proposito agregar prestatario
//Retorno VOID
void agregar_prestatario(Prestatario arreglo[], int& dl_prestatarios) {
    //Inserta elementos(codigo_prestatario, apellidos, nombres)
    system("cls"); //limpia la consola
    string nombre; //variable para almacenar temporalmente lo que ingresa el usuario
    string apellido; //variable para almacenar temporalmente lo que ingresa el usuario

    cout << "\t***AGREGAR PRESTATARIO***" << endl << endl;

    if (dl_prestatarios < DIM_FISICA_PRESTATARIO) {  //Mientras que la dl sea menor que la df

        cout << "Ingrese el nombre del prestatario(ingrese '0' para cancelar): " << flush; //le avisa al usuario para que ingrese el nombre del prestatario, 0 para cancelar
        getline(cin >> ws, nombre); //guarda lo que ongreso el usuario
        if (nombre == "0") { //si ingreso 0 se calncela y se le avisa
            cout << "Se aborto la operacion" << endl;
            presione_enter_funciones();
            return; //regresa al menu
        }

        cout << "Ingrese el apellido del prestatario: " << flush; //le pide al usuario que ingrese un apellido
        getline(cin >> ws, apellido); //guarda temporalmente lo que ingresa el usuario
        for (int x = 0; x < dl_prestatarios; x++) { //itera sobre los prestatarios
            if ((arreglo[x].apellido == arreglo[dl_prestatarios].apellido) && (arreglo[x].nombres == arreglo[dl_prestatarios].nombres)) { //verifica si ya se encuentra ingresado el prestatario
                cout << "El prestatario ya fue ingresado" << endl;
                presione_enter_funciones();
                return; //regresa al menu
            }
        }
        arreglo[dl_prestatarios].nombres = nombre; //guarda lo que se ingreso en la ultima posision logica en 'nombre' de forma definitiva
        arreglo[dl_prestatarios].apellido = apellido; //guarda definitivamente lo que ingresa el usuario ya que no se necesita que cancele
        arreglo[dl_prestatarios].codigo_prestatario = dl_prestatarios + 1; //se le asigna un numero automaticamente al prestatario guardado
        cout << "El prestatario: " << arreglo[dl_prestatarios].nombres << " se agrego correctamente con el codigo: " << arreglo[dl_prestatarios].codigo_prestatario << endl; //se le avisa al usuario que se guardo correctamente el prestatario y con que codigo
        dl_prestatarios++; //aumenta la dimension logica en 1
        presione_enter_funciones();
        return; //regresa al menu
    }
    else { //Cuando la dl es mayor que la df le indicamos que no se pueden agregar m s
        cout << "No se puede agregar mas prestatarios (limite alcanzado)" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }

}

//Proposito: modificar prestatario
//retorno VOID
void modificar_prestatario(Prestatario arreglo[], int& dl_prestatario, Prestamo*& fin) {
    //Es la opcion para modificar a un prestatario del sistema
vuelta: //punto de retorno en caso de que el usuario ingrese un numero que no se encuentra
    system("cls"); //limpia la consola
    int cod_a_mod; //guarta temporalmente la seleccion del usuario
    string nombre; //guarda temporalmente el nombre que ingrese el usuario
    string apellido; //guara temporalmente el apellido que ingrese el usuario

    cout << "\t***MODIFICAR PRESTATARIO***" << endl << endl;

    for (int x = 0; x < dl_prestatario; x++) {  //  Recorremos los prestatarios ya ingresados y los imprime
        cout << "Codigo: " << arreglo[x].codigo_prestatario << ", ";
        cout << "nombre/s y apellido/s: " << arreglo[x].nombres << ", " << arreglo[x].apellido << endl;
    }
    cout << "\nIngrese el codigo del prestatario que quiere modificar(para cancelar ingrese '0'): " << flush; //le pide al usuario que ingrese el codigo del prestatario que quiere modificar
    cin >> cod_a_mod; //guarda temporalmente la seleccion del usuario
    if (cod_a_mod == 0) { //si ingreso 0 se cancela
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    else {
        for (int x = 0; x < dl_prestatario; x++) { //recorre los prestatarios
            if (arreglo[x].codigo_prestatario == cod_a_mod) { //verifica el codigo que ingreso el usuario con los de los prestatarios hasta que sean iguales
                cout << "Ingrese el nuevo nombre del prestatario: " << flush; //le pide al usuario que ingrese un nuevo nombre
                getline(cin >> ws, nombre); //guarda temporalmente lo que ingreso el usuario
                cout << "Ingrese el nuevo apellido del prestatario: " << flush; //le pide al usuario que ingrese un nuevo apellido
                getline(cin >> ws, apellido); //guarda temporalmente lo que ingreso el usuario
                for (int i = 0; i < dl_prestatario; i++) { //recorre los prestatarios
                    if ((nombre == arreglo[i].nombres) && (apellido == arreglo[i].apellido)) { //verifica que no se encuentre ingresado lo que escribio el usuario
                        cout << "Ese prestatario ya esta presente con el codigo: " << arreglo[i].codigo_prestatario << endl; //se le avisa que ya se encuentra ingresado lo que escribio en caso de que asi sea
                        presione_enter_funciones();
                        return; //regresa al menu
                    }
                }
                cout << "El nombre del prestatario '" << arreglo[x].codigo_prestatario << "' fue cambiado a '" << nombre << "' y el apellido a '" << apellido << "'" << endl; //le avisa al usuario que se cambio correctamente lo que modifico y con que codigo
                arreglo[x].nombres = nombre; //guarda definitivamente lo que ingreso el usuario
                arreglo[x].apellido = apellido;
                for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera en los prestamos
                    if (aux->codigo_prestatario_p == cod_a_mod) { //si coinciden los codigos
                        aux->nombre_p = nombre; //reemplaza el nombre en los prestamos
                        aux->apellido_p = apellido; //reemplaza el apellido en los prestamos
                    }
                }
                presione_enter_funciones();
                return; //regresa al menu
            }
        }
    }
    //llegado a este punto significa que no ingreso un codigo valido
    cout << "El codigo ingresado no pertenece a ninguna categoria" << endl;
    presione_enter_submenus();
    goto vuelta; //vuelve a 'vuelta' en caso de que el codigo ingresado no pertenesca a ningun prestatario
}

//Proposito: eliminar prestatario
//retorno VOID
void eliminar_prestatario(Prestamo*& fin, Prestatario arreglo[], int& dl_prestatario) {
    //Es la opcion para remover a un prestatrio del sistema
    //Se le pedira confirmacionn para eliminar al prestatario

vuelta: //punto de retorno en caso de no se elimine ningun prestatario
    system("cls"); //limpia la consola
    int cod_a_del; //guarda temporalmente la seleccion del usuario
    bool estado;

    cout << "\t***ELIMINAR PRESTATARIO***" << endl << endl;

    for (int x = 0; x < dl_prestatario; x++) {  //recorre la lista de los prestatarios y los imprime
        cout << "Codigo: " << arreglo[x].codigo_prestatario << ", ";
        cout << "Nombre/s y apellido/s: : " << arreglo[x].nombres << ", " << arreglo[x].apellido << endl;
    }
    cout << "\nIngrese el codigo del prestatario que quiere eliminar(ingrese '0' para cancelar): " << flush; //le pide al usuario que ingrese un codigo para seleccionar, 0 para cancelar
    cin >> cod_a_del; //guarda temporalmente la seleccion del usuario


    if (cod_a_del == 0) { // se abora la operacion si el numero elegido es 0
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    verificar_estado_prestatario(fin, cod_a_del, estado); //llama a la funcion para verificar el estado, le pasa por parametro la lista, el codigo elegido y la variable estado
    if (estado == true) { //si estado resulto verdadero
        cout << "El prestatario no puede eliminarse debido a que tiene asociado prestamos pendientes" << endl;
        presione_enter_submenus();
        goto vuelta; //regresa a vuelta
    }
    else {
        for (int x = 0; x < dl_prestatario; x++) { //recorre los prestatarios
            if (cod_a_del == arreglo[x].codigo_prestatario) { // verifica hasta que encuentra el codigo que ingreso el usuario
                for (int i = x; i < dl_prestatario - 1; i++) {    // recorre los prestatario
                    arreglo[i] = arreglo[i + 1];  // reemplaza lo que esta en 'i' con el siguiente y asi hasta que llegue al final de la dimension logica
                    arreglo[i].codigo_prestatario--;   // resta en uno los codigos ya que se elimino un elemento
                }
                dl_prestatario--; // resta la dimension logica ya que se elimino un elemento
                cout << "Se elimino el prestatario con exito" << endl; //se le avisa al usuario que se elimino con exito
                presione_enter_submenus();
                return; //regresa al menu
            }
        }
        //llegado a este punto significa que no ingreso un codigo valido
        cout << "El codigo ingresado no pertenece a ningun prestatario" << endl;
        presione_enter_submenus();
        goto vuelta; //vuelve a 'vuelta' en caso de que el codigo ingresado no pertenesca a ningun prestatario
    }
}

// ******SUBMENU 2*******

//Proposito: agregar un prestamo
//retorno VOID
void agregar_prestamo(Prestamo*& fin, int& dl_prestamo, Categoria arregloC[], int& dl_categoria, Prestatario arregloPR[], int& dl_prestatario) {
    //agregar un prestamo
    system("cls"); //limpia la consola
    char respuesta; //guarda temporalmente la seleccion del usuario
    int codigo; //guarda temporalmente la seleccion del usuario

    cout << "\t***AGREGAR PRESTAMO***" << endl << endl;

    //Mostramos las categorias para que el usuario elija una
    if (dl_prestamo < DIM_FISICA_PRESTAMO) {
    vuelta_categorias: //punto de retorno en caso de que el usuario no elija S/N o que no exista el codigo que ingrese

        cout << "\250Desea ver la lista de las categorias?(S/N): " << flush; // \250 = ' ', se le pregunta al usuario que si desea ver o no las categorias
        cin >> respuesta; //se guarda temporalmente la seleccion del usuario

        if (toupper(respuesta) == 'S') { //se convierte a mayuscula la respuesta del usuario y se compara con 'S'
            for (int x = 0; x < dl_categoria; x++) { //en caso de que ingrese s o S recorre las categorias y las imprime

                cout << "Codigo: " << arregloC[x].codigo_categoria << ", ";
                cout << "descripcion: " << arregloC[x].descripcion << endl;
            }
            cout << "\nIngrese el codigo de una categoria(0 para cancelar): " << flush; //le pide al usuario que seleccione un codigo
        }
        else if (toupper(respuesta) == 'N') { //se convierte a mayuscula la respuesta del usuario y se compara con 'N'
            cout << "\nIngrese el codigo de una categoria(0 para cancelar): " << flush; //le pide al usuario que ingrese un un codigo
        }
        else { //en caso de que no elija S ni N se le pregunta de vuleta hasta que responda con alguna
            system("cls"); //limpia la consola
            cout << "\t***AGREGAR PRESTAMO***" << endl << endl;

            cout << "Por favor elija (S/N)" << endl;
            goto vuelta_categorias; //vuelve a 'vuelta_categoria' para que el usuario lo intente de vuelta
        }
        cin >> codigo; //guarda temporalmente el codigo que ingreso el usuario
        if (codigo == 0) {
            cout << "Se aborto la operacion" << endl;
            presione_enter_submenus();
            return; //regresa al menu
        }
        else if (codigo > dl_categoria || codigo < 0) { //Si el codigo no pertenece a ninguna opcion se le avisa al usuario
            cout << "El codigo ingresado no pertenece a ninguna categoria" << endl;
            presione_enter_submenus();
            goto vuelta_categorias; //vuelve a 'vuelta_categoria' en caso de que el codigo ingresado no pertenesca a ningun prestatario
        }

        Prestamo* nuevo = new Prestamo; //se crea un nuevo nodo

        nuevo->codigo_p = dl_prestamo + 1; //genera automaticamente un codigo para el prestamo
        nuevo->codigo_categoria_p = codigo;
        nuevo->descripcion_categoria_p = arregloC[codigo - 1].descripcion; //ingresa la descripcion de la categoria asocioada a una descripcion aparte de la que ingresa el usuario
        system("cls"); //limpia la consola

    vuelta_prestatarios: //punto de retorno en caso de que el usuario no elija S/N o que no exista el codigo que ingrese

        cout << "\t***AGREGAR PRESTAMO***" << endl << endl;


        cout << "\250Desea ver la lista de los prestatarios?(S/N): "; // \250 = ' ', se le pregunta al usuario que si desea ver o no los prestatarios
        cin >> respuesta; //se guarda temporalmente la seleccion del usuario
        if (toupper(respuesta) == 'S') { //se convierte a mayuscula la respuesta del usuario y se compara con 'S'
            for (int x = 0; x < dl_prestatario; x++) { //en caso de que ingrese s o S recorre las categorias y las imprime
                cout << "Codigo: " << arregloPR[x].codigo_prestatario << ", ";
                cout << "Nombre/s y apellido/s: " << arregloPR[x].nombres << ", " << arregloPR[x].apellido << endl;
            }
            cout << "\nIngrese el codigo del prestatario: " << flush; //le pide al usuario que seleccione un codigo
        }
        else if (toupper(respuesta) == 'N') { //se convierte a mayuscula la respuesta del usuario y se compara con 'N'
            cout << "\nIngrese el codigo del prestatario: " << flush; //le pide al usuario que seleccione un codigo
        }
        else { //en caso de que no elija S ni N se le pregunta de vuleta hasta que responda con alguna
            system("cls"); //limpia la consola
            cout << "\t***AGREGAR PRESTAMO***" << endl << endl;
            cout << "Por favor elija (S/N)" << endl;
            goto vuelta_prestatarios; //vuelve a 'vuelta_prestatarios' para que el usuario lo intente de vuelta
        }
        cin >> codigo;
        if (codigo > dl_prestatario || codigo < 0) { //Si el codigo no pertenece a ninguna opcion se le avisa al usuario
            cout << "El codigo ingresado no pertenece a ninguna categoria" << endl;
            presione_enter_submenus();
            goto vuelta_prestatarios; //vuelve a 'vuelta_prestatarios' en caso de que el codigo ingresado no pertenesca a ningun prestatario
        }
        nuevo->nombre_p = arregloPR[codigo - 1].nombres; //guarda definitivamente todos los datos
        nuevo->apellido_p = arregloPR[codigo - 1].apellido;
        nuevo->codigo_prestatario_p = codigo;

        cout << "\nIngrese una descripcion del prestamo: " << flush; //le pide al usuario que ingrese una descripcion
        getline(cin >> ws, nuevo->descripcion_p); //guarda definitivamente la descripcion

        nuevo->estado_p = true; //asigna el estado 'true' para indicar que ya esta activo
        dl_prestamo++; //aumenta la dimesion logica en 1
        cout << "\nSe agrego correctamente el prestamo"; //avisa al usuario que se agrego correctamente el prestamo

        nuevo->siguiente = nullptr; //al siguiente le asigna nullptr
        insertar_final(fin, nuevo); //llama a la funcion y le pasa por parametro la lista y el nodo nuevo
        presione_enter_funciones();
        return; //regresa al menu
    }
    else { //en caso de que la dimension logica sea = 0 > que la fisica se le avisa que no se puede guardar mas
        cout << "No se puede agregar mas categorias(limite alcanzado)" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
}
//Proposito: Modificar un prestamo
//Retorno VOID
void modificar_prestamo(Prestamo*& fin) {
    //modificar un prestamo por algun error
vuelta: //punto de retorno en caso de que el usuario elija un codigo inexistente
    system("cls"); //limpia la consola
    int cod_a_mod; //guarda temporalmente la seleccion del usuario

    cout << "\t***MODIFICAR PRESTAMO***" << endl;


    imprimir_lista(fin); //llama a la funcion para imprimir las listas

    cout << "\nIngrese un codigo para seleccionar un prestamo(ingrese '0' para cancelar): " << flush; //le indica al usuario que ingrese un codigo para seleccionar el prestamo
    cin >> cod_a_mod; //guarda temporalmente la seleccion del usuario

    if (cod_a_mod == 0) { //si la seleccion se 0 se calncela y se le avisa al usuario
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    else {
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
            if (cod_a_mod == aux->codigo_p) { // verifica el codigo seleccionado con los de los prestamos hasta que es verdadero
                cout << "Ingrese una nueva descripcion: " << flush; // le pide al usuario que ingrese una nueva descripcion
                getline(cin >> ws, aux->descripcion_p); //guarda definitivamente lo que ingreso el usuario
                cout << "Se modifico la descripcion con exito" << endl; // le avisa al usuario que se modifico con exito
                presione_enter_funciones();
                return; //regresa al menu
            }
        }
    }
    if (cod_a_mod != 0) { //si el codigo no pertenece a ningun prestamo se le avisa al usuario
        cout << "El codigo ingresado no pertenece a ningun prestamo" << endl;
        presione_enter_submenus();
        goto vuelta; //vuelve a 'vuelta' en caso de que el codigo ingresado no pertenesca a ningun prestamo
    }

}
//Proposito: Eliminar prestamo
//Retorno VOID
void eliminar_prestamo(Prestamo*& fin, int& dl_prestamo) {
    //Eliminar un prestramo por cancelacion o algun otro motivo
vuelta: //punto de retorno en caso de que el usuario elija un codigo inexistente
    system("cls"); //limpia la consola
    int cod_a_del; //guarda temporalmente la seleccion del usuario
    bool estado; //guarda temporalmente el estado 

    cout << "\t***ELIMINAR PRESTAMO***" << endl << endl;;

    if (fin == nullptr) { //verifica que tenga nodos
        cout << "No hay prestamos para eliminar" << endl;
        presione_enter_submenus();
        return;
    }


    imprimir_lista(fin); //llama a la funcion para imprimir la lista

    cout << "\nIngrese un codigo para seleccionar un prestamo(ingrese '0' para cancelar): " << flush; //le indica al usuario que ingrese un codigo para seleccionar el prestamo
    cin >> cod_a_del; //guarda temporalmente la seleccion del usuario

    if (cod_a_del == 0) { //si la seleccion es 0 se cancela
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return; //regresa al menu
    }
    verificar_estado_prestamo(fin, cod_a_del, estado); //llama a la funcion para vrificar el estado del prestamo seleccionado
    if (estado == true) { //si esta activo no se eleimina, sino pasa a la siguiente instruccion
        cout << "El prestamo no puede eliminarse debido a que esta activo" << endl;
        presione_enter_submenus();
        goto vuelta; //se dirige a vuelta
    }

    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) //recorre los prestamos
        if (aux->codigo_p == cod_a_del) { //si el codigo es igual al elegido
            eliminar(fin, cod_a_del); //llama a la funcion eliminar que pasa la lista y el codigo elegido
            cout << "El prestamo se elimino con exito" << endl;

            dl_prestamo--; //se decrementa la dimencion logica
            presione_enter_submenus();
            return;
        }

    //en caso de que el programa llegue a este punto significa que no ingreso un codigo valido
    cout << "El codigo ingresado no pertenece a ningun prestamo" << endl;
    presione_enter_submenus();
    goto vuelta; //vuelve a 'vuelta' en caso de que el codigo ingresado no pertenesca a ningun prestamo

}

//Proposito: devolver prestamo
//Retorno VIOD
void devolver_prestamo(Prestamo*& fin) {
    //devolver prestamo
    system("cls"); //limpia la consola
    int cod_a_sel_1, cod_a_sel_2; //variables para guardar los codigos de prestatarios y prestamos que introduzca el usuario
    map<int, pair<string, string>> prestatarios; //creacion de diccionario para guardar los codigos de los prestatarios como key y los nombres y apellidos como valores    

    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera sobre los prestamos
        if (aux->estado_p == true)
            prestatarios.insert({ aux->codigo_prestatario_p, make_pair(aux->nombre_p, aux->apellido_p) }); //guarda en el diccionario prestatarios el codigo en key por lo tanto no se repiten y los nombres y apellidos
    }

    if (prestatarios.empty() == true) { // verifica que el diccionario no tenga elementos y por lo tanto de que no hay prestamos activos
        cout << "No hay prestamos a devolver." << endl;
        presione_enter_submenus();
        return;
    }

vuelta_1:

    cout << "\t***DEVOLVER PRESTAMO***" << endl << endl;

    cout << "\t   --Prestatarios--" << endl << endl;

    cout << left << setw(10) << "Codigo:" << "Nombre y apellido:" << endl;

    for (auto x = prestatarios.begin(); x != prestatarios.end(); x++) { //itera sobre el diccionario
        cout << right << setw(4) << x->first << "      " << x->second.first << " " << x->second.second << endl; //imprime el diccionario
    }

    cout << "\nSeleccione un prestatario (0 para cancelar): " << flush;
    cin >> cod_a_sel_1; //guarda el prestatario seleccionado

    if (cod_a_sel_1 == 0) { //si el usuario ingresa 0 se cancela
        cout << "Se aborto la operacion" << endl;
        presione_enter_submenus();
        return;
    }

    map<int, int> prestamos; //creacion de diccionario para guardar los codigos autogenerados como keys y el codigo de cada prestamo como valor

vuelta_2: //punto de retorno
    int codigo = 1; //inicializaciono de varible en 1 para los codigos autogenerados
    for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera sobre los prestamos para encontrar el prestatario
        if (cod_a_sel_1 == aux->codigo_prestatario_p) { //si el codigo que ingreso el usuario es igual al que se encuantra actualmente en aux continua

            cout << "\nEl prestatario " << aux->nombre_p << " " << aux->apellido_p << " tiene los siguientes prestamos asociados:" << endl; //imprime el nombre y apellido del prestatario seleccionado

            for (Prestamo* aux2 = fin; aux2 != nullptr; aux2 = aux2->siguiente) { //itera sobre los prestamos para encontrar los prestamos asociados

                if (aux->codigo_prestatario_p == aux2->codigo_prestatario_p && aux2->estado_p == true) { //si coinciden los codigos se encontro un prestamo
                    cout << "Codigo: " << codigo << ", categoria: " << aux2->descripcion_p << ", descripcion: " << aux2->descripcion_p << endl; //imprime el codigo autogenerado, la descripcion de la categoria y la descripcion dada por el usuario
                    prestamos.insert({ codigo, aux2->codigo_p }); //guarda el codigo autogenerado como key y el codigo de la categoria como valor

                    codigo++; //aumenta el codigo autogenerado
                }

            }goto continuar; //se dirige hacia continuar (no se uso break por si el usuario elejia un numero que no se encontrara disponible)
        }
    }

    if (cod_a_sel_1 != 0) { //si no existe el codigo ingresado se cancela
        cout << "El codigo que introdujo no pertenece a ningun prestatario con prestamos" << endl;
        presione_enter_submenus();
        goto vuelta_1;
    }


continuar: //punto de retorno

    cout << "\nSeleccione un prestamo a devolver(0 para cancelar): " << flush;
    cin >> cod_a_sel_2; //guarda el prestamo seleccionado

    if (cod_a_sel_2 == 0) { //si es 0 se cancela
        cout << "Se aborto la operacion" << endl << endl;
        presione_enter_submenus();
        return;
    }

    for (auto x = prestamos.begin(); x != prestamos.end(); x++) { //itera sobre el diccionario de prestamos
        if (x->first == cod_a_sel_2) { //si la key de prestamos es igual a lo ingresado por el usuario continua
            for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera sobre los prestamos
                if (x->second == aux->codigo_p) { //si el valor de la key que se encuentra en x es igual al codigo de aux continua
                    aux->estado_p = false; //cambia el estado del prestamo seleccionado por false
                    cout << "El prestamo se devolvio con exito" << endl;
                    presione_enter_submenus();
                    return;
                }
            }
        }
    }
    //como hay return arriba, si no se accedio al if porque no existe el codigo, regresa a vuelta
    //se repite el texto para dar la impresion de que solo se borro una parte
    cout << "El codigo que introdujo no pertenece a ningun prestamo mostrado, intente nuevamente" << endl;
    presione_enter_submenus();
    cout << "\t***DEVOLVER PRESTAMO***" << endl << endl;

    cout << "\t   --Prestatarios--" << endl << endl;

    cout << left << setw(10) << "Codigo:" << "Nombre y apellido:" << endl;

    for (auto x = prestatarios.begin(); x != prestatarios.end(); x++) { //itera sobre el diccionario
        cout << right << setw(4) << x->first << "      " << x->second.first << " " << x->second.second << endl; //imprime el diccionario
    }

    cout << "\nSeleccione un prestatario (0 para cancelar): " << cod_a_sel_1 << endl;

    goto vuelta_2;

}

//  ******SUBMENU 3*******

//Proposito: Cantidad de objetos prestados por categoria
//Retorno VOID
void cantidad_de_objetos_prestados_por_categoria(Prestamo*& fin, Categoria arregloC[], int& dl_categoria) {
    //Contar las cantidades de objetos prestados segun la categoria que elija
    system("cls"); //limpia la consola
    int total = 0;
    int cant_categoria = 0; //inicializa la variable en 0 para contar la cantindad de prestamos por categoria

    cout << "\t***CANTIDAD DE OBJETOS POR CATEGORA***" << endl << endl;

    if (fin == nullptr) {
        cout << "No se han agregado prestamos" << endl;
        presione_enter_submenus();
        return;
    }
    else {
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //verifica que haya por lo menos 1 prestamo activo
            if (aux->estado_p == true)
                goto continuar; //se dirige a continuar
        }
        //en caso de que no haya encontrado ningun prestamo activo
        cout << "No hay ninguna categoria con prestamos pendientes." << endl;
        presione_enter_submenus();
        return;
    }

continuar:

    cout << left << setw(16) << "Categoria:";
    cout << "Prestamos asociados:" << endl;

    for (int x = 0; x < dl_categoria; x++) { //recorre las categorias
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
            if (arregloC[x].descripcion == aux->descripcion_categoria_p && aux->estado_p == true) { //compara las descripciones de las categorias con las de los prestamos(la que se le asigno automaticamente, no la que ingreso el usuario) y si el estado es 'true' continua
                cant_categoria++; //incrementa la cantidad de cateogrias
                total++; //incrementa el total
            }
        }

        if (cant_categoria != 0) {//si tiene al menos un prestamo asociado continua
            cout << left << setw(25) << arregloC[x].descripcion;
            cout << cant_categoria << endl;
        }
        cant_categoria = 0;//se resetea la variable
    } //se repite hasta la ultima categoria
    cout << "\nHay un total de " << total << " prestamo(s) pendientes(s)" << endl;
    presione_enter_submenus();

}
//Proposito: Listado de prestamos por categoria
//Retorno VOID
void listado_de_prestamos_por_categoria(Prestamo*& fin, Categoria arregloC[], int& dl_categoria) {

    //Muesta la lista de prestamos por categoria que se elija
    system("cls"); //limpia la consola
    int cod_a_sel; //guarda temporalmente la seleccion del usuario
    bool estado;

    cout << "\t***LISTADO DE PRESTAMOS POR CATEGORIA***" << endl << endl;

    if (fin == nullptr) { //verifica si hay por lo menos un elemento
        cout << "No se han agregado prestamos" << endl;
        presione_enter_submenus();
        return;
    }
    else { //si hay 1 por lo menos
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre para ver si hay 1 prestamo que este activo
            if (aux->estado_p == true)
                goto vuelta; //se dirige a vuelta
        }
        //en caso de que no haya encontrado ningun prestamo activo
        cout << "No hay ninguna categoria con prestamos pendientes." << endl;
        presione_enter_submenus();
        return;
    }


vuelta: //punto de retorno

    cout << left << setw(10) << "Codigo:";
    cout << "Descripcion:" << endl;

    for (int x = 0; x < dl_categoria; x++) {  //recorre las categorias y las imprime


        cout << right << setw(4) << arregloC[x].codigo_categoria << "      "; //alinea el texto
        cout << arregloC[x].descripcion << endl;
    }
    cout << "\nIngrese el codigo de la categoria de la que quiere mostrar los prestamos(para cancelar ingrese '0'): " << flush; //se le pide al usuario que ingrese el codigo a seleccionar
    cin >> cod_a_sel; //guarda temporalmente la seleccion del usuario

    if (cod_a_sel == 0) { //si el ususario ingreso 0
        cout << "Se aborto la operacion." << endl;
        presione_enter_submenus();
        return;
    }

    verificar_estado_categoria(fin, cod_a_sel, estado); // llama a la funcion para verificar si la categoria seleccionada tiene algun prestamo activo
    for (int x = 0; x < dl_categoria; x++) { //recorre las categorias
        if (arregloC[x].codigo_categoria == cod_a_sel) { //verifica la seleccion del usuario con los codigos de categoria hasta que sean los mismos
            if (estado == false) { //si no se encontro ninguna categoria con prestamo activo

                cout << "La categoria seleccionada no tiene ningun prestamo activo asocicado" << endl;
                presione_enter_submenus();
                goto vuelta; //va a vuelta
            }
            else {
                cout << "\nLa categoria '" << arregloC[x].descripcion << "' tiene los siguientes prestamos pendientes:" << endl << endl; // imprime la categoria que selecciono el usuario
                cout << left << setw(25) << "Descripcion:"; //alinea el texto
                cout << "Prestatario:" << endl;


                for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
                    if (arregloC[x].descripcion == aux->descripcion_categoria_p && aux->estado_p == true) { // compara las descripciones de las categorias con las de los prestamos(la que se le asigno automaticamente, no la que ingreso el usuario) y si el estado es 'true' continua
                        cout << left << setw(25) << aux->descripcion_p; //alinea el texto e imprime las descripciones que ingreso el usuario a los prestamos y los nombres a quienes fueron prestadas
                        cout << aux->nombre_p + ", " + aux->apellido_p << endl;
                    }
                }
                presione_enter_submenus();
                cout << "\t***LISTADO DE PRESTAMOS POR CATEGORIA***" << endl << endl;
                goto vuelta; //vuelve a vuelta
            }
        }
    }
    //legado a este punto significa que no se selecciono ningun codigo existente
    cout << "El codigo seleccionado no pertenece a ninguna categoria." << endl;
    presione_enter_submenus();
    cout << "\t***LISTADO DE PRESTAMOS POR CATEGORIA***" << endl << endl;
    goto vuelta;
}
//Proposito: listado_de_prestamos_ordenados_por_categoria_o_prestatario
//Retorno VOID
void listado_de_prestamos_ordenados_por_categoria_o_prestatario(Prestamo*& fin, Categoria arregloC[], int& dl_categoria, Prestatario arregloPR[], int& dl_prestatario) {
    //muestra un listado ordenado de los prestamos ordenados por categoria o por prestatario


    char respuesta; //guarda temporalmente la respuesta del usuario
    bool estado; //guarda temporalmente el estado de lo que se quiera verificar
    vector<string> categorias; //vector para guardar las categorias y despues ordenarlas

    system("cls");

    cout << "\t***LISTADO DE PRESTAMOS***" << endl << endl;

    if (fin == nullptr) {
        cout << "No se han agregado prestamos" << endl;
        presione_enter_submenus();
        return;
    }

vuelta: //punto de retorno en caso de que el usuario no elija P ni C
    cout << "\250Clasificar por categoria (C) o prestatario (P)?: " << flush; //le avisa al usuario que ingrese si quiere ordenar por categoria o prestatario
    cin >> respuesta; //guarda temporalmente la respuesta del usuario

    if (toupper(respuesta) == 'C') {  //se convierte la respuesta del usuario a mayuscula y se compara con 'C', si es verdadera...

        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
            if (aux->estado_p == true) //si hay algun prestamo pendiente se dirije a continuar
                goto continuar;
        }
        //en caso de que no haya encontrado ningun prestamo activo
        cout << "No hay ninguna categoria con prestamos pendientes." << endl;
        presione_enter_submenus();
        return;

    continuar:

        for (int x = 0; x <= dl_categoria; x++) { //recorre las categorias
            verificar_estado_categoria(fin, x, estado); //llama a la funcion para verficar el estado y le pasa la lista, x como el codigo y estado para mas a delante cambiarlo
            if (estado == true) { //si el estado resulta true
                categorias.push_back(arregloC[x - 1].descripcion); //agrega la descripcion que tenia x al vector
            }
        }
        categorias = orden_alfabetico(categorias); //reemplaza el vector con lo que retorna la funcion para ordenar alfabeticamente y le pasa el vector sin ordenar como parametro

        for (int x = 0; x < categorias.size(); x++) { //recorre el vector

            cout << "\nLa categoria " << categorias[x] << " esta asosiada a los siguientes prestamos pendientes:" << endl; //imprime el primer elemento del vector
            cout << left << setw(24) << "Descripcion:"; //alinea el texto
            cout << "Nombre y Apellido : " << endl;

            for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera sobre los prestamos

                if (categorias[x] == aux->descripcion_categoria_p && aux->estado_p == true) { //si la string del vector es igual a una de un prestamo y el estado es true continua
                    cout << left << setw(24) << aux->descripcion_p;
                    cout << aux->nombre_p + ", " + aux->apellido_p << endl; //alinea el texto e imprime la descripcion de la categoria y el nombre y apellido del prestatario asociado
                }
            }

        }presione_enter_submenus();
    }
    else if (toupper(respuesta) == 'P') { //se convierte la respuesta del usuario a mayuscula y se compara con 'P', si es verdadera...
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //recorre los prestamos
            if (aux->estado_p == true) //si hay algun prestamo pendiente se dirije a continuar
                goto continuar_1;
        }
        //en caso de que no haya encontrado ningun prestamo activo
        cout << "No hay ningun prestatario con prestamos pendientes." << endl;
        presione_enter_submenus();
        return;

    continuar_1:
        for (int x = 0; x <= dl_prestatario; x++) { //se itera sobre los prestatarios
            verificar_estado_prestatario(fin, x, estado);

            if (estado == true) {

                cout << "\nEl prestatario " << arregloPR[x - 1].nombres << " " << arregloPR[x - 1].apellido << " tiene los siguientes prestamos pendientes:" << endl; //se imprimen los datos de los prestatarios
                cout << left << setw(18) << "Categoria:"; //alinea el texto
                cout << "Descripcion:" << endl;

                for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //se itera sobre los prestamos

                    if (arregloPR[x - 1].codigo_prestatario == aux->codigo_prestatario_p && aux->estado_p == true) { //si coinciden los codigos 
                        cout << left << setw(18) << aux->descripcion_categoria_p; //alinea el texto e imprime la descipcion de la categoria y la dada por el usuario
                        cout << aux->descripcion_p << endl;
                    }
                }
            }
        }presione_enter_submenus();
    }
    else {
        system("cls"); //limpia la consola
        cout << "\t***LISTA DE PRESTAMOS***" << endl << endl;
        cout << "Por favor elija una opcion" << endl;
        goto vuelta; //vuelve a 'vuelta' en caso de que el usuario no ingrese C ni P
    }
}

//Proposito: Listar todos los prestatarios que tienen al menos un objeto prestado
//Proposito VOID
void listar_todos_los_prestatarios_que_tienen_al_menos_un_objeto_prestado(Prestamo*& fin, Prestatario arregloPR[], int& dl_prestatario) {
    //Muestra una lista de todos los prestatarios que tienen al menos un objeto prestado
    system("cls"); //limpia la consola
    int cant_prestamos = 0; //inicializa la variable en 0 para contar la cantindad de prestamos por prestatarios

    cout << "\t***LISTA ADEUDORES***" << endl << endl;

    if (fin == nullptr) { //verifica que haya un elemento por lo menos
        cout << "No se han agreagado prestamos" << endl;
        presione_enter_submenus();
        return;
    }
    else { //si hay un elemento
        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //verifica que haya un prestmo activo por lo menos
            if (aux->estado_p == true) //si hay 1 se dirige a continuar
                goto continuar;
        }
        //en caso de que no haya encontrado ningun prestamo activo
        cout << "No hay ningun prestatario con prestamos pendientes." << endl;
        presione_enter_submenus();
        return;
    }

continuar:

    cout << left << setw(22) << "Prestatario:"; //alinea el texto
    cout << "Prestamos pendientes:" << endl;

    for (int x = 0; x <= dl_prestatario; x++) { //itera sobre los prestatarios

        for (Prestamo* aux = fin; aux != nullptr; aux = aux->siguiente) { //itera sobre los prestamos

            if (arregloPR[x].nombres == aux->nombre_p && aux->estado_p == true) //compara los nombres y el estado y si todo es verdadero continua
                cant_prestamos++; //se aumneta la variable
        }
        if (cant_prestamos != 0) { //si la cantidad de prestamos por prestatario cambio (o sea que por lo menos tiene un prestamo asociado)...
            cout << left << setw(31) << arregloPR[x].nombres + " " + arregloPR[x].apellido;//alinea el texto e imprime el nombre del prestatario y la cantidad de prestamos asociados
            cout << cant_prestamos << endl;
        }
        cant_prestamos = 0; //resetea la variable
    } //se repite hasta que la condicion sea falsa
    presione_enter_submenus();
}

// SUBMENU 1
int submenu_1(char opcion) {
    cout << "Elija una opcion: "; cin >> opcion;

    while (opcion != '0') {
        switch (opcion) {
        case '1':
            agregar_categoria(categorias, dl_categoria);
            break;
        case '2':
            modificar_categoria(categorias, dl_categoria, fin);
            break;
        case '3':
            eliminar_categoria(fin, categorias, dl_categoria);
            break;
        case '4':
            agregar_prestatario(prestatarios, dl_prestatario);
            break;
        case '5':
            modificar_prestatario(prestatarios, dl_prestatario, fin);
            break;
        case '6':
            eliminar_prestatario(fin, prestatarios, dl_prestatario);
            break;
        case '0':
            break;
        default:
            system("cls"); //limpia la consola
            cout << "\t***Opcion invalida***" << endl;
            presione_enter_submenus();
            break;
        }
        cout << "\tAdministrar y consultar Categorias y Prestatarios." << endl << endl;
        cout << "1. Agregar categoria" << endl;
        cout << "2. Modificar categoria" << endl;
        cout << "3. Eliminar categoria" << endl;
        cout << "4. Agregar prestatario" << endl;
        cout << "5. Modificar prestatario" << endl;
        cout << "6. Eliminar prestatario" << endl;
        cout << "0. Volver" << endl << endl;

        cout << "Elija una opcion: "; cin >> opcion;
    }
    system("cls"); //limpia la consola
    return 0;
}

// SUBMENU 2
int submenu_2(char opcion) {
    cout << "Elija una opcion: "; cin >> opcion;
    while (opcion != '0') {
        switch (opcion) {
        case '1': agregar_prestamo(fin, dl_prestamo, categorias, dl_categoria, prestatarios, dl_prestatario);
            break;
        case '2': modificar_prestamo(fin);
            break;
        case '3': eliminar_prestamo(fin, dl_prestamo);
            break;
        case '4': devolver_prestamo(fin);
            break;
        case '0':
            break;
        default:
            system("cls"); //limpia la consola
            cout << "\t***Opcion invalida***" << endl;
            presione_enter_submenus();
            break;
        }
        cout << "\tAdministrar Prestamos" << endl << endl;
        cout << "1. Agregar prestamo" << endl;
        cout << "2. Modificar prestamo" << endl;
        cout << "3. Eliminar prestamo" << endl;
        cout << "4. Devolver prestamo" << endl;
        cout << "0. Volver" << endl << endl;

        cout << "Elija una opcion: "; cin >> opcion;
    }
    system("cls"); //limpia la consola
    return 0;
}

// SUBMENU 3
int submenu_3(char opcion) {
    cout << "Elija una opcion: "; cin >> opcion;
    while (opcion != '0') {
        switch (opcion) {

        case '1': cantidad_de_objetos_prestados_por_categoria(fin, categorias, dl_categoria);
            break;
        case '2': listado_de_prestamos_por_categoria(fin, categorias, dl_categoria);
            break;
        case '3': listado_de_prestamos_ordenados_por_categoria_o_prestatario(fin, categorias, dl_categoria, prestatarios, dl_prestatario);
            break;
        case '4': listar_todos_los_prestatarios_que_tienen_al_menos_un_objeto_prestado(fin, prestatarios, dl_prestatario);
            break;
        case '0':
            break;
        default:
            system("cls"); //limpia la consola
            cout << "\t***Opcion invalida***" << endl;
            presione_enter_submenus();
            break;
        }
        cout << "\tConsultar Prestamos" << endl << endl;
        cout << "1. Cantidad de objetos prestados por categoria" << endl;
        cout << "2. Listado de prestamos por categoria" << endl;
        cout << "3. Listado de prestamos ordenados por categoria o prestatario" << endl;
        cout << "4. Listar todos los prestatarios que tienen al menos un objeto prestado" << endl;
        cout << "0. Volver" << endl << endl;

        cout << "Elija una opcion: "; cin >> opcion;
    }
    system("cls"); //limpia la consola
    return 0;
}

int main() {

    //Inicializacion de variables
    char opcion = 0;

    //MENU PRINCIPAL
    while (opcion != '9') {

        cout << "\tBienvenido al Consultor de Prestamos." << endl << endl;
        cout << "1. Administrar y consultar Categorias y Prestatarios" << endl;
        cout << "2. Administrar Prestamos" << endl;
        cout << "3. Consultar Prestamos" << endl;
        cout << "9. Salir" << endl << endl;

        cout << "Elija una opcion: "; cin >> opcion;


        switch (opcion)
        {
        case '1':       //SUBMENU 1
            system("cls");
            cout << "\tAdministrar y consultar Categorias y Prestatarios." << endl << endl;
            cout << "1. Agregar categoria" << endl;
            cout << "2. Modificar categoria" << endl;
            cout << "3. Eliminar categoria" << endl;
            cout << "4. Agregar prestatario" << endl;
            cout << "5. Modificar prestatario" << endl;
            cout << "6. Eliminar prestatario" << endl;
            cout << "0. Volver" << endl << endl;

            submenu_1(opcion); //llama a la funcion para elejir que hacer en el submenu 1


            break;
        case '2':       //SUBMENU 2
            system("cls");
            cout << "\tAdministrar Prestamos" << endl << endl;
            cout << "1. Agregar prestamo" << endl;
            cout << "2. Modificar prestamo" << endl;
            cout << "3. Eliminar prestamo" << endl;
            cout << "4. Devolver prestamo" << endl;
            cout << "0. Volver" << endl << endl;

            submenu_2(opcion); //llama a la funcion para elejir que hacer en el submenu 2

            break;
        case '3':       //SUBMENU 3
            system("cls");
            cout << "\tConsultar Prestamos" << endl << endl;
            cout << "1. Cantidad de objetos prestados por categoria" << endl;
            cout << "2. Listado de prestamos por categoria" << endl;
            cout << "3. Listado de prestamos ordenados por categoria o prestatario" << endl;
            cout << "4. Listar todos los prestatarios que tienen al menos un objeto prestado" << endl;
            cout << "0. Volver" << endl << endl;

            submenu_3(opcion); //llama a la funcion para elejir que hacer en el submenu 3

            break;
        case '9':
            break;
        default:        //En caso de no elejir una opcion disponible
            system("cls"); //limpia la consola
            cout << "\t***Opcion invalida***" << endl;
            presione_enter_submenus();
            break;
        }

    }
    system("cls"); //limpia la consola
    return 0;
}
