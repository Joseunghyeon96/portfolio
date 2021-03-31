using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LaserXmoveSpawn : MonoBehaviour
{
    public GameObject wallPrefab;
    public float interval = 4.0f;
    private float range = 10.0f;

    IEnumerator Start()
    {
        while (true)
        {
            transform.position = new Vector3(Random.Range(0.0f, 20.0f),
 transform.position.y, transform.position.z);
            Instantiate(wallPrefab, transform.position, transform.rotation);
            yield return new WaitForSeconds(interval);
        }
    }

    void Update()
    {
    }

}
