#include <vorpal/graphics/Camera.hpp>

vp::graphics::Camera::Camera()
    : m_fov(0.0f), m_znear(0.0f), m_zfar(0.0f), m_rotation(glm::vec3()), m_position(glm::vec3()), m_perspective(glm::mat4()), m_view(glm::mat4()), m_rotationSpeed(1.0f), m_movementSpeed(1.0f)
{
}

vp::graphics::Camera::~Camera()
{
}

void vp::graphics::Camera::SetPerspective(float fov, float aspect, float znear, float zfar)
{
    m_fov = fov;
    m_znear = znear;
    m_zfar = zfar;
    m_perspective = glm::perspective(glm::radians(fov), aspect, znear, zfar);
}

void vp::graphics::Camera::UpdateAspectRatio(float aspect)
{
    m_perspective = glm::perspective(glm::radians(m_fov), aspect, m_znear, m_zfar);
}

void vp::graphics::Camera::SetPosition(glm::vec3 position)
{
    m_position = position;
    UpdateViewMatrix();
}

void vp::graphics::Camera::SetRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
    UpdateViewMatrix();
}

void vp::graphics::Camera::Rotate(glm::vec3 delta)
{
    m_rotation += delta;
    UpdateViewMatrix();
}

void vp::graphics::Camera::SetTranslation(glm::vec3 translation)
{
    m_position = translation;
    UpdateViewMatrix();
}

void vp::graphics::Camera::Translate(glm::vec3 delta)
{
    m_position += delta;
    UpdateViewMatrix();
}

void vp::graphics::Camera::UpdateViewMatrix()
{
    glm::mat4 rotM = glm::mat4();
    glm::mat4 transM;

    rotM = glm::rotate(rotM, glm::radians(m_rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    rotM = glm::rotate(rotM, glm::radians(m_rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    rotM = glm::rotate(rotM, glm::radians(m_rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

    transM = glm::translate(glm::mat4(), m_position);
    m_view = rotM * transM;
}
