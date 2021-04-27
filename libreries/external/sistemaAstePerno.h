#include <iostream>
#include <string>

using namespace std;

struct asta
{
    double lunghezza;
    double altezza;

    //posizione perno all'interno dell'asta
    double x;
    double y;
};

struct device
{

    asta astaBase;
    asta astaGiunto;
    float angoloBase;
    float angoloGiunto;
};

asta *SAP_asta_init(double, double);

device *SAP_device_init(double, double, float, float);

bool SAP_controlloAste(double, double);

bool SAP_controlloAngoli(float, float);

void SAP_motoAngolo(float, float, device *);

void SAP_salvaSVG(string SVG);

void SAP_disegnaDevice(device *);

void SAP_distruggiDispositivo(device *);

string SAP_estraiValore(string, string, string);

device *SAP_parse(string);

device *inserisciDati();

void menu(device *);

void SAP_printDevice(device *);
