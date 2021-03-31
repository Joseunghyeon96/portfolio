using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss_FireBall : MonoBehaviour
{
    GameObject parent;
    Rigidbody rigidbody;
    public GameObject spawner;

    public bool isthrow;
    public bool explod;
    float throwTime;

    Vector3 throwPower;

    void Start()
    {
        parent = this.transform.parent.gameObject;
        explod = false;        
        throwPower = new Vector3(0, 100, 0);
        throwTime = 0.5f;
    }

    void Update()
    {
        if (isthrow)
        {
            throwTime -= Time.deltaTime;
            if (throwTime > 0.0f) return;

            if (this.transform.parent != null)
            {
                this.transform.parent = null;
                rigidbody = this.gameObject.AddComponent<Rigidbody>();
                rigidbody.AddForce(throwPower, ForceMode.Impulse);
            }
        }

        if (isthrow && this.transform.position.y > 25)
        {            
            explod = true;
            isthrow = false;
            Destroy(rigidbody);
            this.transform.parent = parent.transform;
            this.transform.position = parent.transform.position;
            throwTime = 0.5f;
            this.gameObject.SetActive(false);
            Instantiate(spawner, GameObject.Find("Boss").gameObject.transform.position+new Vector3(0,3,-5), GameObject.Find("Boss").gameObject.transform.rotation);
        }
    }
}
