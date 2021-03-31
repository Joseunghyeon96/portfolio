using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LaserSpawner : MonoBehaviour
{
    // Start is called before the first frame update
    public GameObject wallPrefab;
    public float interval = 4.0f;
    private float range = 10.0f;
    // Start is called before the first frame update 

    IEnumerator Start ()
    {
        while (true) { transform.position = new Vector3(transform.position.x, 
            Random.Range(10, 10+range), transform.position.z);
            Instantiate(wallPrefab, transform.position, transform.rotation);
            yield return new WaitForSeconds(interval);
        }
    }
    // Update is called once per frame 
    void Update () {

    }
}
