#include <mysql.h>
#include <mysqld_error.h>
#include <fstream>
#include "generar_lista_grupo.h"

#include <iostream>
using namespace std;

struct listaGrupo generar_lista_grupo(string clave_grupo){
    

    /*VARIABLES*/
    struct listaGrupo a;
    MYSQL* coneccion;
    ifstream archivoSQL{ "SCRIPTS/lista_grupo.sql" };
    string ejecutarScript{ istreambuf_iterator<char>(archivoSQL), istreambuf_iterator<char>() };
    string::size_type pos;
    unsigned int num_filas;
    unsigned int num_f = 0;
    const char* _lista;
    MYSQL_RES* res;
    MYSQL_ROW row;
    /*COMIENZA*/
    coneccion = mysql_init(0);
    if (coneccion) {
        coneccion = mysql_real_connect(coneccion, "bj42twrs4vaqpd6iosvg-mysql.services.clever-cloud.com", "uw77bf6ikf5zyq1n", "q8apKjoZ8H2sR6PI2ZI2", "bj42twrs4vaqpd6iosvg", 3306, NULL, 0);
    }
    //REMPLAZAR Clave grupo
    pos = ejecutarScript.find("claveGrupo", 0);
    if (pos < string::npos) {
        ejecutarScript.replace(pos, string("claveGrupo").length(), "\'" + clave_grupo + "\'");
    }
    //TERMINA Clave grupo
    
    _lista = ejecutarScript.c_str();
    mysql_query(coneccion, _lista);
    res = mysql_store_result(coneccion);
    num_filas = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < num_filas; i++) {
            if (row[i] != NULL) {
                a.rs[num_f][i] = row[i];
            }
        }
        num_f = num_f + 1;
    }
    if (res != NULL)
        mysql_free_result(res);

    mysql_close(coneccion);
    return a;
    /*TERMINA*/
}
