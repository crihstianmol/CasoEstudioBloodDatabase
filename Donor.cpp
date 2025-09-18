
/*
    Proyecto: BloodDatabase (Adaptado)
    Curso: Fundamentos de Programación Orientada a Objetos (FPOO)
    Universidad del Valle

    Descripción:
    Este proyecto gestiona una base de datos de donantes de sangre, proporcionando 
    funcionalidades para registrar, buscar y analizar la información de los donantes.

    El código se basó en el proyecto BloodDatabase, fue traducido al español 
    y adaptado a las necesidades del curso.

    

    Autor: Victor Bucheli
    Correo: victor.bucheli@correounivalle.edu.co
    Fecha: Octubre 2024

    Modificado por: Crihstian Molina
    Correo: crihstian.molina@correounivalle.edu.co
    Fecha: Septiembre 2025
    
    Modificaciones:
    - Se agregó la fecha de donación a los donantes.
    - Se cambiaron los tipos de datos para el número de teléfono y el tipo de sangre.
*/
#include "Donor.h"
#include <sstream>
#include <iostream>
#include <algorithm>

void Donor::donorDetails() const {
    std::cout << "Nombre del donante: " << name << std::endl;
    std::cout << "Distrito del donante: " << district << std::endl;
    std::cout << "Tipo de sangre del donante: " << bloodType << std::endl;
}

Donor Donor::parseLine(const std::string& line) {
    Donor d;
    
    if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
        d.donorId = 0;
        d.name = "";
        d.address = "";
        d.district = 0;
        d.bloodType = 0;
        d.number = 0;
        d.donationDate = "";
        return d;
    }
    
    std::stringstream ss(line);
    std::string token;

    getline(ss, token, ','); d.donorId = std::stoi(trim(token));
    getline(ss, token, ','); d.name = trim(token);
    getline(ss, token, ','); d.address = trim(token);
    getline(ss, token, ','); d.district = std::stoi(trim(token));
    getline(ss, token, ','); d.bloodType = std::stoi(trim(token));
    getline(ss, token, ','); d.number = std::stoll(trim(token));
    
    if (std::getline(ss, token, ',')) {
        d.donationDate = trim(token);
    } else {
        d.donationDate = "Fecha no disponible"; 
    }

    return d;
}

std::string Donor::trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
