using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BossStoneSpwan : MonoBehaviour
{
    public GameObject wallPrefab;
    Vector3 pos;
    public float interval = 0.1f;
    int i = 0;    

    IEnumerator Start()
    {
        while (true)
        {
            i++;
            if (i > 10)
            {
                i = 0;
                Destroy(this.gameObject);
            }
            pos = new Vector3(Random.Range(transform.position.x - 10, transform.position.x + 10),
           Random.Range(transform.position.y, transform.position.y + 10), transform.position.z);
            Instantiate(wallPrefab, pos, transform.rotation);
            yield return new WaitForSeconds(interval);
        }
    }    
}
