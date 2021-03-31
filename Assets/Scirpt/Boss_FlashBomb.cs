using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss_FlashBomb : MonoBehaviour
{
    GameObject parent;
    Rigidbody rigidbody;     

    public bool isthrow;
    public bool explod;
    float throwTime;

    Vector3 throwPower;

    void Start()
    {
        parent = this.transform.parent.gameObject;
        explod = false;        
        throwPower = new Vector3(0, 15, -5);
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

        if (isthrow && this.transform.position.y < 14)
        {
            GameObject.Find("Boss").GetComponent<AudioSource>().clip = GameObject.Find("Boss").GetComponent<Boss>().flb;
            GameObject.Find("Boss").GetComponent<AudioSource>().Play();
            explod = true;
            isthrow = false;
            Destroy(rigidbody);
            this.transform.parent = parent.transform;
            this.transform.position = parent.transform.position;
            throwTime = 0.5f;
            this.gameObject.SetActive(false);
        }
    }


    void OnCollisionEnter(Collision collision)
    {
        GameObject.Find("Boss").GetComponent<AudioSource>().clip = GameObject.Find("Boss").GetComponent<Boss>().flb;
        GameObject.Find("Boss").GetComponent<AudioSource>().Play();
        explod = true;
        isthrow = false;
        Destroy(rigidbody);
        this.transform.parent = parent.transform;
        this.transform.position = parent.transform.position;
        throwTime = 0.5f;
        this.gameObject.SetActive(false);
    }
}
