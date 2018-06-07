#include "Bazooka.h"
#include "types.h"
#include <iostream>

Bazooka::Bazooka(int id, b2World& world, float posX, float posY, float mirrored, 
float shooting_angle, int power_factor, weapon_t type) : 
Weapon(type),
bazookaPhysic(world, posX, posY, this) {
    this->exploded = false;
    this->power_factor = power_factor;
    this->mirrored = mirrored;
    this->shooting_angle = shooting_angle;
    this->id = id;
    this->contact = false;
    this->blast_power = gConfiguration.BAZOOKA_BLAST_POWER;
    this->blast_radius = gConfiguration.BAZOOKA_BLAST_RADIUS;
    shoot();
}

void Bazooka::explode() {
    this->bazookaPhysic.explode(this->blast_radius, this->blast_power);
    this->exploded = true;
}

float Bazooka::getPosX() {
    return this->bazookaPhysic.getPosX();
}

float Bazooka::getPosY() {
    return this->bazookaPhysic.getPosY();
}

void Bazooka::shoot() {
    this->bazookaPhysic.shoot(mirrored, shooting_angle, power_factor);
}

void Bazooka::update(int currenTime) {
    if (this->bazookaPhysic.getPosY() > gConfiguration.WORLD_Y_LIMIT || contact) {
        this->explode();
        std::cout << "BAZOOKA FUERA DE RANGO " << std::endl;
    }
}

void Bazooka::setContact(bool made_contact) {
    this->contact = made_contact;
}

