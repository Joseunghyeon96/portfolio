using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayScript : MonoBehaviour
{

    public RaycastHit HitObj;
    private Ray ray;

    public float MaxRayDistance = 0.5f;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    private void FixedUpdate()
    {
        if (Physics.Raycast(transform.position, transform.forward, out HitObj, MaxRayDistance))
        {
            Debug.DrawRay(transform.position, transform.forward * HitObj.distance, Color.green);
        }
        else
        {
            Debug.DrawRay(transform.position, transform.forward * MaxRayDistance, Color.red);
        }


    }

    public bool GetIsRayHit()
    {
        return Physics.Raycast(transform.position, transform.forward, out HitObj, MaxRayDistance);
    }
}
