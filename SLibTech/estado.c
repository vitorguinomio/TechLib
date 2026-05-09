#include "estado.h"

// ================= TEXTO ESTADO =================
char* textoEstado(EstadoLivro estado) {

    switch(estado) {

        case DISPONIVEL:
            return "Disponivel";

        case EMPRESTADO:
            return "Emprestado";

        case DANIFICADO:
            return "Danificado";

        case IMPRESTAVEL:
            return "Imprestavel";

        default:
            return "Desconhecido";
    }
}