using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class fireball : MonoBehaviour
{
    GameObject target;
    Vector3 targetPos;

    AudioSource audio;
    float audioTime;

    void Start()
    {
        this.audio = this.GetComponent<AudioSource>();        
        
        target = GameObject.Find("Player").GetComponent<PlayerController>().Player[
            GameObject.Find("Player").GetComponent<PlayerController>().player_seq].gameObject;
        targetPos = new Vector3(this.transform.position.x, 10.0f, target.transform.position.z + 5);
        Destroy(this.gameObject, 7.0f);
        audioTime = 0.5f;
        targetPos = targetPos - this.transform.position;
    }

    void Update()
    {
        audioTime -= Time.deltaTime;
        if (audioTime < 0.0f)
        {                        
            if (!this.audio.isPlaying)                
            this.audio.Play();
        }
        this.transform.rotation = Quaternion.Euler(0, 0, 0);
        this.transform.Translate(targetPos * Time.deltaTime / 2);
    }

    void OnCollisionEnter(Collision collision)
    {        
        if (collision.gameObject.tag == "Player")
        {
            GameObject.Find("Player").GetComponent<PlayerController>().stun = true;
        }
    }
}
