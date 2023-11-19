#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <cmath>

struct Equipo {
    std::string nombre;
    int fuerza;
    int puntos;
    int golesAnotados;
    int golesEnContra;
    std::string estadio;
};

struct Partido {
    Equipo equipoLocal;
    Equipo equipoVisitante;
    int golesLocal;
    int golesVisitante;
    std::string estadio;
};

void simularPartido(Partido& partido) {
    // Simulación de goles aleatorios
    partido.golesLocal = rand() % 4;
    partido.golesVisitante = rand() % 4;

    // Actualizar estadísticas de los equipos por referencia
    Equipo& equipoLocal = partido.equipoLocal;
    Equipo& equipoVisitante = partido.equipoVisitante;

    equipoLocal.golesAnotados += partido.golesLocal;
    equipoLocal.golesEnContra += partido.golesVisitante;

    equipoVisitante.golesAnotados += partido.golesVisitante;
    equipoVisitante.golesEnContra += partido.golesLocal;

    // Determinar ganador
    if (partido.golesLocal > partido.golesVisitante) {
        equipoLocal.puntos += 3;
    } else if (partido.golesVisitante > partido.golesLocal) {
        equipoVisitante.puntos += 3;
    } else {
        equipoLocal.puntos += 1;
        equipoVisitante.puntos += 1;
    }
}

void simularFase(std::vector<Equipo>& equipos, const std::string& estadio) {
    std::random_shuffle(equipos.begin(), equipos.end());

    for (int i = 0; i < equipos.size(); i += 2) {
        Partido partido{equipos[i], equipos[i + 1], 0, 0, estadio};
        simularPartido(partido);
        std::cout << "----- Partido -----" << std::endl;
        std::cout << partido.equipoLocal.nombre << " vs " << partido.equipoVisitante.nombre << std::endl;
        std::cout << "Resultado: " << partido.golesLocal << " - " << partido.golesVisitante << std::endl;
        std::cout << "Estadio: " << estadio << std::endl;
    }
}

void imprimirTabla(const std::vector<Equipo>& equipos) {
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << std::setw(15) << "Equipo" << std::setw(10) << "Puntos" << std::setw(15) << "Gf" << std::setw(15) << "Gc" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    for (const auto& equipo : equipos) {
        std::cout << std::setw(15) << equipo.nombre << std::setw(10) << equipo.puntos << std::setw(15) << equipo.golesAnotados << std::setw(15) << equipo.golesEnContra << std::endl;
    }

    std::cout << "--------------------------------------------------------" << std::endl;
}

void simularTorneo(std::vector<Equipo>& equipos) {
    std::vector<std::string> estadios = {"Camp Nou", "Bernabeu", "Sevilla Dourmout", "La Bombonera"};
    for (const auto& estadio : estadios) {
        simularFase(equipos, estadio);
        imprimirTabla(equipos);
    }

    std::cout << "----- Fase Eliminatoria -----" << std::endl;
    while (equipos.size() > 1) {
        Partido partido{equipos[0], equipos[1], 0, 0, estadios[0]};
        simularPartido(partido);
        std::cout << "----- Partido -----" << std::endl;
        std::cout << partido.equipoLocal.nombre << " vs " << partido.equipoVisitante.nombre << std::endl;
        std::cout << "Resultado: " << partido.golesLocal << " - " << partido.golesVisitante << std::endl;
        std::cout << "Estadio: " << estadios[0] << std::endl;

        // Eliminar al equipo perdedor y avanzar al ganador
        equipos.erase(equipos.begin() + 1);
        imprimirTabla(equipos);
    }

    // Imprimir al ganador del torneo
    std::cout << "El ganador del mundial es: " << equipos[0].nombre << "!" << std::endl;
}

int main() {
    // Configuración inicial
    srand(static_cast<unsigned int>(time(nullptr)));

    // Crear equipos
    std::vector<Equipo> equipos = {
        {"Argentina", rand() % 100, 0, 0, 0, ""},
        {"Brazil", rand() % 100, 0, 0, 0, ""},
        {"Colombia", rand() % 100, 0, 0, 0, ""},
        {"Chile", rand() % 100, 0, 0, 0, ""},
        {"Peru", rand() % 100, 0, 0, 0, ""},
        {"Inglaterra", rand() % 100, 0, 0, 0, ""},
        {"Francia", rand() % 100, 0, 0, 0, ""},
        {"Paises Bajos", rand() % 100, 0, 0, 0, ""},
    };

    // Simular el torneo completo
    simularTorneo(equipos);

    return 0;
}
