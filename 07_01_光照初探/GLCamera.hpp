#ifndef GL_CAMERA_H__
#define GL_CAMERA_H__

#include <GLObject.hpp>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>


class GLCamera : public GLObject {
public:
    GLCamera();

    bool init();
    void draw();
    virtual void update(GLfloat delta);

    inline glm::mat4 & viewMatrix(){
        return m_viewMatrix;
    }

    inline glm::mat4 & projectionMatrix(){
        return m_projectionMatrix;
    }

    inline glm::mat4 & modelMatrix(){
        return m_modelMatrix;
    }

    inline glm::vec3 & center(){
        m_center = front() + position();
        return m_center;
    }

    inline glm::vec3 & right(){
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        return m_right;
    }

    inline void moveEye(float leftSpeed, float frontSpeed){
        setPosition(position() + leftSpeed * right() + frontSpeed * front());
    }

    inline void moveDirection(float x, float y){
        m_yaw += x;
//        if( m_yaw > m_maxYaw ){
//            m_yaw = m_maxYaw;
//        }else if( m_yaw < m_minYaw ){
//            m_yaw = m_minYaw;
//        }

        m_pitch += y;
        if( m_pitch > maxPitch() ){
            m_pitch = maxPitch();
        }else if( m_pitch < minPitch() ){
            m_pitch = minPitch();
        }

        glm::vec3 newFront(cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw)),
                  sin(glm::radians(m_pitch)),
                  cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw)));
        setFront(newFront);
    }

    inline glm::vec3 & worldUp() {
        return m_worldUp;
    }

    inline void setWorldUp(const glm::vec3 & value) {
        m_worldUp = value;
    }


    inline glm::vec3 & position(){
        return m_position;
    }

    inline void setPosition(const glm::vec3 & value){
        m_position = value;
    }

    inline glm::vec3 & front(){
        return m_front;
    }

    inline void setFront(const glm::vec3 & value){
        m_front = glm::normalize(value);
    }

    inline GLfloat minYaw() const{
        return m_minYaw;
    }

    inline void setMinYaw(const GLfloat &value){
        m_minYaw = value;
    }

    inline GLfloat maxYaw() const{
        return m_maxYaw;
    }

    inline void setMaxYaw(const GLfloat &value){
        m_maxYaw = value;
    }

    inline GLfloat minPitch() const {
        return m_minPitch;
    }

    inline void setMinPitch(const GLfloat &value){
        m_minPitch = value;
    }

    inline GLfloat maxPitch() const{
        return m_maxPitch;
    }

    inline void setMaxPitch(const GLfloat &value){
        m_maxPitch = value;
    }

    inline GLfloat zNearPane() const{
        return m_zNearPane;
    }

    inline void setZNearPane(const GLfloat &value){
        m_zNearPane = value;
        m_projectionMatrix = glm::perspective(m_fovy, m_aspect, m_zNearPane, m_zFarPane);
    }

    inline GLfloat zFarPane() const{
        return m_zFarPane;
    }

    inline void setZFarPane(const GLfloat &value){
        m_zFarPane = value;
        m_projectionMatrix = glm::perspective(m_fovy, m_aspect, m_zNearPane, m_zFarPane);
    }

    inline GLfloat fovy() const{
        return m_fovy;
    }

    inline void setFovy(const GLfloat &value){
        m_fovy = glm::radians(value);
        m_projectionMatrix = glm::perspective(m_fovy, m_aspect, m_zNearPane, m_zFarPane);
    }

    inline GLfloat aspect() const{
        return m_aspect;
    }

    inline void setAspect(const GLfloat &value){
        m_aspect = value;
        m_projectionMatrix = glm::perspective(m_fovy, m_aspect, m_zNearPane, m_zFarPane);
    }

private:
    GLfloat m_yaw;
    GLfloat m_pitch;
    glm::vec3 m_worldUp;
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_center;
    glm::mat4 m_viewMatrix;

    glm::mat4 m_modelMatrix;

    glm::mat4 m_projectionMatrix;
    GLfloat m_minYaw;
    GLfloat m_maxYaw;
    GLfloat m_minPitch;
    GLfloat m_maxPitch;
    GLfloat m_zNearPane;
    GLfloat m_zFarPane;
    GLfloat m_fovy;
    GLfloat m_aspect;
};

#endif//GL_CAMERA_H__
