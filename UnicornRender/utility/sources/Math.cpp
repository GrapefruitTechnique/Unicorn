/*
* Copyright (C) 2017 by Godlike
* This code is licensed under the MIT license (MIT)
* (http://opensource.org/licenses/MIT)
*/

#include <unicorn/utility/Math.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/norm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace unicorn
{
namespace utility
{
namespace math
{

glm::quat RotationBetweenVectors(glm::vec3 start, glm::vec3 dest, glm::vec3 worldX, glm::vec3 worldZ)
{
    start = glm::normalize(start);
    dest = glm::normalize(dest);

    float const cosTheta = glm::dot(start, dest);
    glm::vec3 rotationAxis;


    if (cosTheta < -1 + SystemAccuracy()) // they look in different sides
    {
        rotationAxis = glm::cross(worldZ, start);
        if (glm::length2(rotationAxis) < SystemAccuracy()) // they are parallel
        {
            rotationAxis = glm::cross(worldX, start);
        }
        rotationAxis = glm::normalize(rotationAxis);

        return glm::angleAxis(glm::radians(180.0f), rotationAxis);
    }

    rotationAxis = glm::cross(start, dest);

    float const s = glm::sqrt((1 + cosTheta) * 2);
    float const invs = 1 / s;

    return glm::quat(
        s * 0.5f,
        rotationAxis.x * invs,
        rotationAxis.y * invs,
        rotationAxis.z * invs
    );
}

glm::quat CalculateOrientationQuaternion(glm::vec3 direction, glm::vec3 desiredUp, glm::vec3 worldY, glm::vec3 worldZ)
{
    if (glm::length2(direction) < SystemAccuracy()) // Already look at desired direction
    {
        return glm::quat();
    }

    glm::vec3 const right = glm::cross(direction, desiredUp);
    desiredUp = glm::cross(right, direction);

    glm::quat const rot1 = RotationBetweenVectors(worldZ, direction);
    glm::quat const rot2 = RotationBetweenVectors(worldY, desiredUp);

    return rot2 * rot1;
}

glm::vec3 RotateAroundPoint(glm::vec3 originalTranslation, float radians, glm::vec3 axis, glm::vec3 point)
{
    glm::vec3 dir = point - originalTranslation;
    glm::vec3 outputTranslation = originalTranslation + dir;
    glm::quat q = glm::angleAxis(radians, axis);
    outputTranslation = outputTranslation + q * -dir;
    return outputTranslation;
}

glm::mat4 AssimpMatrixToGlm(aiMatrix4x4 const& from)
{
    glm::mat4 to;
    to[0][0] = from.a1;
    to[1][0] = from.a2;
    to[2][0] = from.a3;
    to[3][0] = from.a4;
    to[0][1] = from.b1;
    to[1][1] = from.b2;
    to[2][1] = from.b3;
    to[3][1] = from.b4;
    to[0][2] = from.c1;
    to[1][2] = from.c2;
    to[2][2] = from.c3;
    to[3][2] = from.c4;
    to[0][3] = from.d1;
    to[1][3] = from.d2;
    to[2][3] = from.d3;
    to[3][3] = from.d4;

    return to;
}

}
}
}
