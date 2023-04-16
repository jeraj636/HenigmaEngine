
#include "transformacija.h"

#include "../../renderer/renderer.h"
#include "../../objekt/objekt.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void Transformacija::zanka()
{
}

Transformacija::Transformacija()
    : pozicija(0.0, 0.0, 0.0), velikost(1.0, 1.0, 1.0), rotacija(0.0, 0.0, 0.0)
{
}
