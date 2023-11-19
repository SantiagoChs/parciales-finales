#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Equipo {
    std::string nombre;
    int puntos;

    Equipo(const std::string& nombre) : nombre(nombre), puntos(0) {}
};

struct Partido {
    Equipo equipoA;
    Equipo equipoB;
    std::string estadio;
    int duracion; // en minutos
    int faltasEquipoA;
    int faltasEquipoB;
    int cambiosEquipoA;
    int cambiosEquipoB;

    Partido(const Equipo& a, const Equipo& b, const std::string& estadio, int duracion)
        : equipoA(a), equipoB(b), estadio(estadio), duracion(duracion), faltasEquipoA(0), faltasEquipoB(0), cambiosEquipoA(0), cambiosEquipoB(0) {}
};

void simularPartido(Partido& partido) {
    for (int minuto = 1; minuto <= partido.duracion; ++minuto) {
        // Simular faltas (10% de probabilidad por minuto)
        if (rand() % 100 < 10) {
            if (rand() % 2 == 0) {
                partido.faltasEquipoA++;
            } else {
                partido.faltasEquipoB++;
            }
        }

        // Simular cambios (5% de probabilidad por minuto)
        if (rand() % 100 < 5) {
            if (rand() % 2 == 0) {
                partido.cambiosEquipoA++;
            } else {
                partido.cambiosEquipoB++;
            }
        }
    }

    int resultado = rand() % 3;
    if (resultado == 0) {
        partido.equipoA.puntos += 3;
    } else if (resultado == 1) {
        partido.equipoA.puntos += 1;
        partido.equipoB.puntos += 1;
    } else {
        partido.equipoB.puntos += 3;
    }
}

std::string seleccionarEstadioAleatorio() {
    std::vector<std::string> estadios = {"Estadio Camp Nou", "Estadio Maracana", "Estadio Monumental", "Estadio Allianz Arena", "Estadio nacional de Beijing", "Estadio Azteca", "Estadio Wembley,"};
    int indiceEstadio = rand() % estadios.size();
    return estadios[indiceEstadio];
}

int main() {
    std::ifstream archivo("datos.txt");

    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo de equipos." << std::endl;
        return 1;
    }

    std::vector<Equipo> equipos;
    std::string nombreEquipo;

    while (std::getline(archivo, nombreEquipo)) {
        equipos.emplace_back(nombreEquipo);
    }

    archivo.close();

    srand(static_cast<unsigned>(time(0)));

    while (equipos.size() > 1) {
        std::vector<Equipo> equiposGanadores;
        std::vector<Partido> partidos;

        for (size_t i = 0; i < equipos.size(); i += 2) {
            std::string estadio = seleccionarEstadioAleatorio();
            std::cout << equipos[i].nombre << " vs " << equipos[i + 1].nombre << " en " << estadio << ": ";

            int duracionPartido = rand() % 120 + 60; // Duración entre 60 y 180 minutos
            Partido partido(equipos[i], equipos[i + 1], estadio, duracionPartido);

            simularPartido(partido);

            std::cout << partido.equipoA.puntos << " - " << partido.equipoB.puntos << " en "
                      << partido.duracion << " minutos\n";
            std::cout << "Faltas: " << partido.faltasEquipoA + partido.faltasEquipoB << " | ";
            std::cout << "Cambios: " << partido.cambiosEquipoA + partido.cambiosEquipoB << "\n";

            partidos.push_back(partido);

            if (partido.equipoA.puntos > partido.equipoB.puntos) {
                equiposGanadores.push_back(partido.equipoA);
            } else {
                equiposGanadores.push_back(partido.equipoB);
            }
        }

        std::cout << "\nEquipos clasificados para la siguiente ronda:\n";
        for (const auto& equipo : equiposGanadores) {
            std::cout << equipo.nombre << "\n";
        }

        equipos = equiposGanadores;
        std::cout << "\n";
    }

    std::cout << "El ganador del torneo es: " << equipos[0].nombre << "" << std::endl;

    return 0;
}