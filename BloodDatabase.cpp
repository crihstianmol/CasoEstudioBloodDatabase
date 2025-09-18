
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
    - Se agregó la visualización de los tipos de sangre.
    - Se modificó la visualización de los departamentos.
    - Se cambiaron los tipos de datos para el número de teléfono y el tipo de sangre.
    - Se cambió la forma de buscar un donante (agregando validaciones para el tipo de sangre).
    - Se agregaron funciones auxiliares para convertir números a texto descriptivo.
    - Se agregaron funciones auxiliares para obtener una entrada válida de tipo long long.
    - Se agregaron funciones auxiliares para obtener la fecha y hora actual.
*/
#include "BloodDatabase.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include <ctime>
#include <iomanip>

using namespace std;

static const std::vector<std::string> departments = {
    "", 
    "Putumayo",
    "Cauca", 
    "Valle del Cauca",
    "Amazonas",
    "Risaralda",
    "Antioquia",
    "Norte de Santander",
    "Chocó",
    "Arauca",
    "Guainía"
};

static const std::vector<std::string> bloodTypes = {
    "", 
    "A+",
    "A-",
    "B+",
    "B-",
    "AB+",
    "AB-",
    "O+",
    "O-"
};

void BloodDatabase::displayProvinces() {
    std::cout << "Elige el departamento:\n";
    for (size_t i = 1; i < departments.size(); i++) {
        std::cout << i << ". " << departments[i] << std::endl;
    }
}

void BloodDatabase::displayBloodTypes() {
    std::cout << "Elige el tipo de sangre:\n";
    for (size_t i = 1; i < bloodTypes.size(); i++) {
        std::cout << i << ". " << bloodTypes[i] << std::endl;
    }
}

std::string BloodDatabase::getDepartmentName(int departmentNumber) {
    if (departmentNumber >= 1 && departmentNumber < static_cast<int>(departments.size())) {
        return departments[departmentNumber];
    }
    return "Desconocido";
}

std::string BloodDatabase::getBloodTypeName(int bloodTypeNumber) {
    if (bloodTypeNumber >= 1 && bloodTypeNumber < static_cast<int>(bloodTypes.size())) {
        return bloodTypes[bloodTypeNumber];
    }
    return "Desconocido";
}

std::string BloodDatabase::getCurrentDateTime() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void BloodDatabase::clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    //   system("clear");
#endif
}

void BloodDatabase::waitForKeyPress() {
    std::cout << "Presiona cualquier tecla para continuar...";
    std::cin.ignore();
    std::cin.get();
}

int BloodDatabase::getValidatedInput(const std::string& prompt) {
    int value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                throw std::invalid_argument("La entrada contiene caracteres no numéricos");
            }
            value = std::stoi(input);
            break; 
        } catch (const std::invalid_argument& e) {
            std::cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Entrada fuera de rango. Por favor ingrese un número válido." << std::endl;
        }
    }
    return value;
}

long long BloodDatabase::getValidatedInputLongLong(const std::string& prompt) {
    long long value;
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        try {
            if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                throw std::invalid_argument("La entrada contiene caracteres no numéricos");
            }
            value = std::stoll(input);
            break; 
        } catch (const std::invalid_argument& e) {
            std::cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Entrada fuera de rango. Por favor ingrese un número válido." << std::endl;
        }
    }
    return value;
}

int BloodDatabase::getOptionalValidatedInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, input);
        
        if (input.empty()) {
            return 0;
        }
        
        try {
            if (!std::all_of(input.begin(), input.end(), ::isdigit)) {
                throw std::invalid_argument("La entrada contiene caracteres no numéricos");
            }
            int value = std::stoi(input);
            
            if (value < 1 || value > 8) {
                std::cout << "Por favor ingrese un número entre 1 y 8, o deje en blanco para omitir." << std::endl;
                continue;
            }
            
            return value;
        } catch (const std::invalid_argument& e) {
            std::cout << "Entrada no válida: " << e.what() << ". Por favor ingrese un número válido o deje en blanco." << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Entrada fuera de rango. Por favor ingrese un número válido o deje en blanco." << std::endl;
        }
    }
}

void BloodDatabase::getDonorDetails() {
    clearConsole();
    std::cout << "Ingrese los detalles del donante\n";

    Donor newDonor;
    newDonor.donorId = getValidatedInput("Id: ");
    std::cout << "Nombre: ";
    std::getline(std::cin, newDonor.name);
    std::cout << "Dirección: ";
    std::getline(std::cin, newDonor.address);

    displayProvinces();
    newDonor.district = getValidatedInput("Departamento (ingrese el número correspondiente): ");
    displayBloodTypes();
    newDonor.bloodType = getValidatedInput("Tipo de sangre (ingrese el número correspondiente): ");
    newDonor.number = getValidatedInputLongLong("Número: ");
    newDonor.donationDate = getCurrentDateTime();

    donors.push_back(newDonor);
}

void BloodDatabase::writeDataToFile() {
    std::ofstream outfile(fileName, std::ios::app);

    if (!outfile) {
        std::cout << "Error al abrir el archivo para escribir." << std::endl;
        return;
    }

    Donor newDonor = donors.back();
    outfile << newDonor.donorId << ",    " << newDonor.name << ",    " << newDonor.address << ",    " << newDonor.district << ",    " << newDonor.bloodType << ",    " << newDonor.number << ",    " << newDonor.donationDate << std::endl;

    outfile.close();
}

void BloodDatabase::searchAndDisplay() const {
    clearConsole();
    displayProvinces();
    int provinceName = getValidatedInput("Ingrese el número de la departamento: ");

    std::cout << "Ingrese la dirección (dejar en blanco para omitir): ";
    std::string addressFilter;
    std::getline(std::cin, addressFilter);

    displayBloodTypes();
    int bloodTypeFilter = getOptionalValidatedInput("Ingrese el tipo de sangre (dejar en blanco para omitir): ");

    std::ifstream inFile(fileName);

    if (!inFile) {
        std::cout << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    std::vector<Donor> donors;
    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        
        if (d.donorId == 0) {
            continue;
        }
        
        bool match = d.district == provinceName &&
            (addressFilter.empty() || d.address.find(addressFilter) != std::string::npos) &&
            (bloodTypeFilter == 0 || d.bloodType == bloodTypeFilter);

        if (match) {
            donors.push_back(d);
            found = true;
        }
    }

    if (!found) {
        std::cout << "No se encontraron personas del departamento " << getDepartmentName(provinceName);
        if (!addressFilter.empty()) {
            std::cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (bloodTypeFilter != 0) {
            std::cout << " y tipo de sangre '" << getBloodTypeName(bloodTypeFilter) << "'";
        }
        std::cout << "." << std::endl;
    } else {
        std::cout << "\n\nPersonas del departamento " << getDepartmentName(provinceName);
        if (!addressFilter.empty()) {
            std::cout << " con dirección que contiene '" << addressFilter << "'";
        }
        if (bloodTypeFilter != 0) {
            std::cout << " y tipo de sangre '" << getBloodTypeName(bloodTypeFilter) << "'";
        }
        std::cout << ":" << std::endl;
        for (const auto& d : donors) {
            std::cout << "\nNombre: " << d.name << std::endl;
            std::cout << "Dirección: " << d.address << std::endl;
            std::cout << "Departamento: " << getDepartmentName(d.district) << std::endl;
            std::cout << "Tipo de sangre: " << getBloodTypeName(d.bloodType) << std::endl;
            std::cout << "Número de móvil: " << d.number << std::endl;
            std::cout << "Fecha de donación: " << d.donationDate << std::endl;
            std::cout << std::endl;
        }
    }

    inFile.close();
    waitForKeyPress();
}

void BloodDatabase::deleteDonor(const std::string& donorName) {
    std::ifstream inFile(fileName);
    std::ofstream tempFile("temp.txt");

    if (!inFile) {
        std::cerr << "Error al abrir el archivo " << fileName << std::endl;
        return;
    }

    if (!tempFile) {
        std::cerr << "Error al crear el archivo temporal" << std::endl;
        return;
    }

    std::string line;
    bool found = false;

    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        
        if (d.donorId == 0) {
            continue;
        }
        
        if (d.name == donorName) {
            found = true;
            std::cout << "Nombre: " << d.name << std::endl;
            std::cout << "Dirección: " << d.address << std::endl;
            std::cout << "Departamento: " << getDepartmentName(d.district) << std::endl;
            std::cout << "Tipo de sangre: " << getBloodTypeName(d.bloodType) << std::endl;
            std::cout << "Número de móvil: " << d.number << std::endl;
            std::cout << "Fecha de donación: " << d.donationDate << std::endl;
            std::cout << std::endl;
            std::cout << "¿Está seguro de que desea eliminar al donante? [s/n]: ";
            char sureChoice;
            std::cin >> sureChoice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

            if (sureChoice == 's' || sureChoice == 'S') {
                continue;
            }
        }

        tempFile << d.donorId << ",    " << d.name << ",    " << d.address << ",    " << d.district << ",    " << d.bloodType << ",    " << d.number << ",    " << d.donationDate << std::endl;
    }

    inFile.close();
    tempFile.close();

    if (std::remove(fileName.c_str()) != 0) {
        std::cerr << "Error al eliminar el archivo original" << std::endl;
        return;
    }

    if (std::rename("temp.txt", fileName.c_str()) != 0) {
        std::cerr << "Error al renombrar el archivo temporal" << std::endl;
        return;
    }

    if (!found) {
        std::cout << "No se encontró ningún donante con el nombre " << donorName << std::endl;
    }
}

void BloodDatabase::displayHistory() const {
    clearConsole();
    std::cout << "=== HISTORIAL DE DONACIONES ===" << std::endl;
    std::cout << "Mostrando donantes ordenados por fecha de donación (más reciente primero):\n" << std::endl;

    std::ifstream inFile(fileName);
    if (!inFile) {
        std::cout << "Error al abrir el archivo para leer." << std::endl;
        return;
    }

    std::vector<Donor> allDonors;
    std::string line;

    
    while (std::getline(inFile, line)) {
        Donor d = Donor::parseLine(line);
        if (d.donorId != 0) { 
            allDonors.push_back(d);
        }
    }
    inFile.close();

    if (allDonors.empty()) {
        std::cout << "No hay donantes registrados en el sistema." << std::endl;
        waitForKeyPress();
        return;
    }

    
    std::sort(allDonors.begin(), allDonors.end(), [](const Donor& a, const Donor& b) {
        return a.donationDate > b.donationDate;
    });

    
    for (size_t i = 0; i < allDonors.size(); i++) {
        const Donor& d = allDonors[i];
        std::cout << "[" << (i + 1) << "] " << d.name << std::endl;
        std::cout << "    ID: " << d.donorId << std::endl;
        std::cout << "    Dirección: " << d.address << std::endl;
        std::cout << "    Departamento: " << getDepartmentName(d.district) << std::endl;
        std::cout << "    Tipo de sangre: " << getBloodTypeName(d.bloodType) << std::endl;
        std::cout << "    Teléfono: " << d.number << std::endl;
        std::cout << "    Fecha de donación: " << d.donationDate << std::endl;
        std::cout << std::endl;
    }

    std::cout << "Total de donaciones: " << allDonors.size() << std::endl;
    waitForKeyPress();
}
