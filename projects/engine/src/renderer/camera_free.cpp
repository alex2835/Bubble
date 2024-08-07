
#include "engine/renderer/camera_free.hpp"

namespace bubble
{
void FreeCamera::ProcessMovement( CameraMovement direction )
{
    f32 max_speed = mMaxSpeed * mDeltaSpeed;

    // Speed x
    if( direction == CameraMovement::FORWARD )
    {
        if( mSpeedX < 0 )
            mSpeedX = 0;
        mSpeedX = mSpeedX < max_speed ? mSpeedX + mDeltaSpeed : max_speed;
        mIsMovingX = true;
    }
    else if( direction == CameraMovement::BACKWARD )
    {
        if( mSpeedX > 0 )
            mSpeedX = 0;
        mSpeedX = mSpeedX > -max_speed ? mSpeedX - mDeltaSpeed : -max_speed;
        mIsMovingX = true;
    }

    // Speed y
    if( direction == CameraMovement::RIGHT )
    {
        if( mSpeedY < 0 )
            mSpeedY = 0;
        mSpeedY = mSpeedY < max_speed ? mSpeedY + mDeltaSpeed : max_speed;
        mIsMovingY = true;
    }
    else if( direction == CameraMovement::LEFT )
    {
        if( mSpeedY > 0 )
            mSpeedY = 0;
        mSpeedY = mSpeedY > -max_speed ? mSpeedY - mDeltaSpeed : -max_speed;
        mIsMovingY = true;
    }

    // Speed z
    // ...

    // Clamp
    if( std::abs( mSpeedX ) > max_speed )
        mSpeedX = Sign( mSpeedX ) * max_speed;

    if( std::abs( mSpeedY ) > max_speed )
        mSpeedY = Sign( mSpeedY ) * max_speed;
}


void FreeCamera::ProcessMouseMovement( f32 mousePosX, f32 mousePosY )
{
    f32 xoffset = ( mLastMouseX - mousePosX ) * mMouseSensitivity;
    f32 yoffset = ( mLastMouseY - mousePosY ) * mMouseSensitivity;

    mLastMouseX = mousePosX;
    mLastMouseY = mousePosY;

    mYaw -= xoffset;
    mPitch -= yoffset;

    if( mPitch > camera::PI / 2.0f - 0.1f )
        mPitch = camera::PI / 2.0f - 0.1f;

    if( mPitch < -camera::PI / 2.0f + 0.1f )
        mPitch = -camera::PI / 2.0f + 0.1f;
}

void FreeCamera::ProcessMouseMovementOffset( f32 xoffset, f32 yoffset )
{
    xoffset *= mMouseSensitivity;
    yoffset *= mMouseSensitivity;

    mYaw += xoffset;
    mPitch += yoffset;

    if( mPitch > camera::PI / 2.0f - 0.1f )
        mPitch = camera::PI / 2.0f - 0.1f;

    if( mPitch < -camera::PI / 2.0f + 0.1f )
        mPitch = -camera::PI / 2.0f + 0.1f;
}


void FreeCamera::ProcessMouseScroll( f32 offset )
{
    if( mFov >= 0.1f && mFov <= camera::PI / 2.0f )
        mFov += offset * mDeltaFov;

    if( mFov < 0.1f )
        mFov = 0.1f;

    if( mFov > camera::PI / 2.0f )
        mFov = camera::PI / 2.0f;
}

void FreeCamera::OnUpdate( DeltaTime dt )
{
    // Inertia
    if( !mIsMovingX )
        mSpeedX = std::abs( mSpeedX ) < 0.01f ? mSpeedX = 0 : mSpeedX - Sign( mSpeedX ) * mDeltaSpeed;

    if( !mIsMovingY )
        mSpeedY = std::abs( mSpeedY ) < 0.01f ? mSpeedY = 0 : mSpeedY - Sign( mSpeedY ) * mDeltaSpeed;

    mIsMovingX = false;
    mIsMovingY = false;

    mPosition += mFront * mSpeedX * dt.Seconds();
    mPosition += mRight * mSpeedY * dt.Seconds();

    UpdateCameraVectors();
}

}