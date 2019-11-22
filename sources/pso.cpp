#include <random>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include <chrono>
#include <thread>
#include "../headers/pso.hpp"

#define UP (1.0)
#define LO (0.0)
#define MAX_ITER (1000)
#define size (0.1)
#define FUNC(x) (1.0/(1.0 + exp(-x)))
#define NUM_PARTICLES (55)
#define NUM_MICROSECS (0)

Particle::Particle() {
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> p_runif(LO, UP);
   std::uniform_real_distribution<> v_runif(-abs(UP - LO), abs(UP - LO));

   m_position = m_best = p_runif(gen);
   m_velocity = v_runif(gen);
   m_fitness = FUNC(m_position);
}

void Particle::updateVelocity(double velocity) {
   m_velocity = velocity;
}

void Particle::updatePosition(void) {
   m_position += m_velocity;
}

void Particle::updateBest(double best) {
   m_best = best;
}

double Particle::position(void) {
   return m_position;
}

double Particle::best(void) {
   return m_best;
}

double Particle::fitness(void) {
   return m_fitness;
}

double Particle::velocity(void) {
   return m_velocity;
}


double Particle::acceler_coef(void) {
   return m_acceler_coef;
}

double Particle::inertia(void) {
   return m_inertia;
}

PSO::~PSO() {
   for (auto p : m_swarm) {
      delete p;
   }
}

void PSO::create_population(int population_size) {
   m_population_size = population_size;
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> runif(LO, UP);
   m_global_best = runif(gen);
   m_swarm.resize(0);

   for (int i = 0; i < population_size; ++i) {
      m_swarm.push_back(new Particle());
      if (FUNC(m_swarm[i]->position()) > m_swarm[i]->fitness()) {
         m_global_best = m_swarm[i]->position();
      }
   }
}

double PSO::start() {
   create_population(NUM_PARTICLES);
   std::random_device rd;
   std::mt19937 gen(rd());
   std::uniform_real_distribution<> runif(LO, UP);
   int iter = 0;
   
   while (iter < MAX_ITER) {
      for (auto particle : m_swarm) {
         particle->updateVelocity(
            particle->velocity()  * particle->inertia() + 
            (particle->acceler_coef() * runif(gen)) * (particle->best() - particle->position()) +
            (particle->acceler_coef() * runif(gen)) * (m_global_best -  particle->position())
         );
         particle->updatePosition();
         // Find local best position
         if (FUNC(-particle->position()) > particle->fitness()) {
            particle->m_best = particle->position();
            particle->m_fitness = (1.0 / (1.0 + exp(-(particle->position()))));
         }
         // Find global best position
         if ((1.0 / (1.0 + exp(-(m_global_best)))) > particle->fitness()) {
            m_global_best = particle->position();
         }
         // Set color
         glColor3f(1
                  , particle->fitness()
                  , particle->position());
         
         glBegin(GL_TRIANGLE_FAN);
            glVertex3f(cos(particle->position()) / 2, particle->position() + size / 2, 0);
            glVertex3f(sin(particle->position()), particle->position() + size / 2, 0);
            glVertex3f(sin(particle->position()), particle->position() - size / 2, 0);
            glVertex3f(sin(particle->fitness() - size / 2), particle->best() + size / 2, 0);
         glEnd();
         glRotatef(particle->fitness(), particle->position(), particle->position(), particle->position());
         // To make animation a bit smoother
         std::this_thread::sleep_for(std::chrono::microseconds(NUM_MICROSECS));
      }
      iter++;
   }
   return m_global_best;
}
