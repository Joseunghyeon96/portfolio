using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class camera : MonoBehaviour
{
    Transform player_pos;

    float dist = 4.0f;

    float xSpeed = 220.0f;
    float ySpeed = 100.0f;

    float x = 0.0f;
    float y = 0.0f;

    float yMinLimit = -50f;
    float yMaxLimit = 80f;

    float ClampAngle(float angle, float min, float max)
    {
        if (angle < -360)
            angle += 360;

        if (angle > 360)
            angle -= 360;

        return Mathf.Clamp(angle, min, max);
    }

    void Start()
    {
        LoadSceneEvent.Instance.hideCursor();
        Vector3 angles = transform.eulerAngles;

        x = angles.y;
        y = angles.x;

        player_pos = GameObject.Find("Player").transform;
    }

    void Update()
    {
        if (Cursor.lockState == CursorLockMode.None) return;
        //dist -= 0.5f * Input.mouseScrollDelta.y;

        //if (dist < 3.0f)
        //    dist = 3;
        //if (dist >= 10)
        //    dist = 10;

        x += Input.GetAxis("Mouse X") * xSpeed * 0.015f;
        y -= Input.GetAxis("Mouse Y") * ySpeed * 0.015f;

        y = ClampAngle(y, yMinLimit, yMaxLimit);

        Quaternion rotation = Quaternion.Euler(y, x, 0);
        Vector3 position = rotation * new Vector3(0.0f, 0.9f, -dist) + player_pos.position + new Vector3(0.0f, 0.0f, 0.0f);

        transform.rotation = rotation;
        transform.position = position;
    }
}
