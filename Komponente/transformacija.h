#pragma once
#include "../Ostalo/ostalo.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include "komponenta.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Objekt/objekt.h"
#include "../Render/render.h"
class Transformacija : public Komponenta
{

public:
        void nastavi(Objekt *kazObj, Okno *kazOkno) override;
        void zanka() override;
        Transformacija();
        Vec3 pozicija;
        Vec3 rotacija;
        Vec3 velikost;
        glm::mat4 matrica;

private:
        uint _lokMatrice;
        /*
         glm::mat4 Mpoz;
         glm::mat4 Mvel;
         glm::mat4 Mrot;
         */
};
