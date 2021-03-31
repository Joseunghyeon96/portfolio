using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BrokeBlock : MonoBehaviour
{
    public GameObject obj;
    public ParticleSystem particle;
    void Start()
    {
        //particle.Stop();
    }

    void Update()
    {
       
    }
    private void OnCollisionEnter(Collision collision)
    {
        if(collision.gameObject.tag == "Power")
        {
            Instantiate(obj, transform.position, transform.rotation);
            particle.Play();
            this.gameObject.GetComponent<MeshRenderer>().enabled = false;
            this.gameObject.GetComponent<BoxCollider>().isTrigger = true;
            Destroy(this.gameObject, 10f);
        }
    }
}
