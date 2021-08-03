using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CameraRotation : MonoBehaviour
{
    public float sensitivity = 500f; //감도 설정

    float rotationY = 0.0f;  //z축 회전값
    public Camera MainCamera;

    public RaycastHit rayHit;
    GameObject hitObject;
    private Ray ray;

    void Start()
    {

    }

    void Update()
    {
        TurnYCamera();
    }

    void TurnYCamera()
    {
        float y = Input.GetAxis("Mouse Y");
        rotationY += y * sensitivity * Time.deltaTime;

        if (rotationY > 15)
        {
            rotationY = 15;
        }
        else if (rotationY < -80)
        {
            rotationY = -80;
        }
        transform.eulerAngles = new Vector3(-rotationY, transform.eulerAngles.y, 0.0f);
    }

    
}
