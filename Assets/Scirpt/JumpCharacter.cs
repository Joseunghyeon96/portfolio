using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JumpCharacter : MonoBehaviour
{
    public GameObject[] costume = new GameObject[3];

    AudioSource audio;
    public AudioClip jumpSound;
    public AudioClip stunSound;

    public int jumpCount;

    public float moveSpeed;
    public bool isBoost;
    public float boostTime;

    Animator animator;

    float stunTime;
    bool dead;

    void Start()
    {
        int whatCostume = GameObject.Find("DataController").GetComponent<DataController>().Get_costume(0);
        costume[whatCostume].transform.SetAsFirstSibling();
        for (int i = 0; i < 3; i++)
            if (i != whatCostume) costume[i].SetActive(false);

        this.gameObject.SetActive(false);

        this.audio = this.gameObject.GetComponent<AudioSource>();
        this.audio.loop = false;
        animator = GetComponent<Animator>();
        jumpCount = 2;

        moveSpeed = 4.0f;
        isBoost = false;
        boostTime = 2.0f;

        dead = false;
        stunTime = 2.0f;

        this.gameObject.SetActive(true);
    }

    void Update()
    {
        animator.SetBool("run", false);

        if (isBoost)
        {
            boostTime -= Time.deltaTime;
            if (boostTime <= 0)
            {
                isBoost = false;
                moveSpeed = 4.0f;
            }
        }

        if (this.transform.position.y <= 8.0f)
        {
            dead = true;
            GameObject.Find("Player").GetComponent<PlayerController>().dead = true;
        }

        if (GameObject.Find("Player").GetComponent<PlayerController>().stun)
        {
            this.audio.clip = stunSound;
            if (this.audio.isPlaying == false)
                this.audio.Play();

            animator.SetBool("stun", true);
            stunTime -= Time.deltaTime;
            if (stunTime <= 0.0f)
            {
                stunTime = 2.0f;
                GameObject.Find("Player").GetComponent<PlayerController>().stun = false;
            }
        }
        else animator.SetBool("stun", false);

        if (dead) animator.SetBool("dead", true);

        if (GameObject.Find("Player").GetComponent<PlayerController>().stun || dead) return;
        if (GameObject.Find("Player").GetComponent<PlayerController>().cameraView) return;
        #region 플레이어 무브
        if (Input.GetKey(KeyCode.UpArrow))
        {
            this.transform.rotation = Quaternion.Euler(0, 0, 0);
            if (Input.GetKey(KeyCode.LeftArrow)) this.transform.rotation = Quaternion.Euler(0, -45, 0);
            if (Input.GetKey(KeyCode.RightArrow)) this.transform.rotation = Quaternion.Euler(0, 45, 0);
            this.transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            this.transform.rotation = Quaternion.Euler(0, 180, 0);
            if (Input.GetKey(KeyCode.LeftArrow)) this.transform.rotation = Quaternion.Euler(0, -135, 0);
            if (Input.GetKey(KeyCode.RightArrow)) this.transform.rotation = Quaternion.Euler(0, 135, 0);
            this.transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            if (!Input.GetKey(KeyCode.UpArrow) && !Input.GetKey(KeyCode.DownArrow))
            {
                this.transform.rotation = Quaternion.Euler(0, -90, 0);
                this.transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);
            }
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            if (!Input.GetKey(KeyCode.UpArrow) && !Input.GetKey(KeyCode.DownArrow))
            {
                this.transform.rotation = Quaternion.Euler(0, 90, 0);
                this.transform.Translate(Vector3.forward * moveSpeed * Time.deltaTime);
            }
            animator.SetBool("run", true);
        }
        #endregion

        if (Input.GetKeyDown(KeyCode.C) && jumpCount > 0)
        {
            this.GetComponent<Rigidbody>().velocity = new Vector3(0.0f, 10f, 0.0f);
            jumpCount--;
            animator.SetBool("jump", true);

            this.audio.clip = jumpSound;
            this.audio.Play();
        }

    }

    void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "stoneMonster" || other.gameObject.tag == "Fire")
        {
            dead = true;
            GameObject.Find("Player").GetComponent<PlayerController>().dead = true;
        }
    }

    void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag == "ground" || other.gameObject.tag == "Boost" || other.gameObject.tag == "Slow")
        {
            animator.SetBool("jump", false);
            jumpCount = 2;
        }

        if (other.gameObject.tag == "Boost")
        {
            moveSpeed = 8.0f;
            boostTime = 2.0f;
            isBoost = true;
        }

        if (other.gameObject.tag == "Slow")
        {
            moveSpeed = 2.0f;
        }

        if (other.gameObject.tag == "Stun")
        {
            GameObject.Find("Player").GetComponent<PlayerController>().stun = true;
        }

        if (other.gameObject.tag == "Finish")
        {
            GameObject.Find("Player").GetComponent<PlayerController>().clear = true;
        }

        if (other.gameObject.tag == "Stone")
        {
            GameObject.Find("UIController").GetComponent<UIController>().clear = true;

        }
    }

    void OnCollisionExit(Collision other)
    {
        if (other.gameObject.tag == "Slow")
        {
            moveSpeed = 4.0f;
        }
    }
}