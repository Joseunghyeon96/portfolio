using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Boss : MonoBehaviour
{
    Animator animator;
    public AudioSource audio;
    public AudioClip flb;
    public AudioClip fb;
    float throwAniTime;

    public GameObject FlashBomb;
    public GameObject FireBall;

    public bool throwFlashBomb;
    public bool throwFireBall;
    float bombTime;

    public bool bossEnd;
    public bool bossClear;

    int what;
    bool number;

    bool oneTime;

    Vector3 direction = new Vector3(0, 0, -1);

    void Start()
    {
        animator = this.GetComponent<Animator>();
        this.audio = this.gameObject.GetComponent<AudioSource>();
        this.audio.loop = false;

        throwFlashBomb = false;
        throwFireBall = false;

        bombTime = 8.0f;
        throwAniTime = 1.0f;
        bossEnd = false;
        animator.SetBool("start", true);
        oneTime = true;
        bossClear = false;
        FlashBomb.SetActive(false);
        FireBall.SetActive(false);
        number = true;
    }

    void Update()
    {
        if (GameObject.Find("UIController").GetComponent<UIController>().bossStageStart)
            return;
        else
        {
            if (oneTime)
            {
                animator.SetBool("start", false);
                this.gameObject.transform.position = new Vector3(10, 16, 37.5f);
                oneTime = false;
            }
        }

        if (bossClear || GameObject.Find("UIController").GetComponent<UIController>().clear)
        {
            animator.SetBool("dead", true);
            return;
        }

        if (this.gameObject.transform.position.z >= 790)
        {
            bossEnd = true;
            return;
        }

        if (throwFlashBomb)
        {
            if (number)
            {
                what = Random.Range(1,4) ;
                if (what == 1)
                {
                    FireBall.SetActive(true);
                    FireBall.GetComponent<Boss_FireBall>().isthrow = true;
                }
                else
                {                    
                    FlashBomb.SetActive(true);
                    FlashBomb.GetComponent<Boss_FlashBomb>().isthrow = true;
                }
                number = false;
            }
            this.transform.rotation = Quaternion.Euler(0, 0, 0);
            direction = new Vector3(0, 0, 1);
            throwAniTime -= Time.deltaTime;
            if (throwAniTime > 0.0f) animator.SetBool("throw", true);
            else
            {
                animator.SetBool("throw", false);
                throwFlashBomb = false;
                number = true;
                if (what == 1)
                {
                    this.audio.clip = fb;
                    this.audio.Play();
                }
            }
        }
        else
        {
            direction = new Vector3(0, 0, -1);
            this.transform.rotation = Quaternion.Euler(0, 180, 0);
            throwAniTime = 1.0f;
            bombTime -= Time.deltaTime;
            if (bombTime <= 0)
            {
                bombTime = 8.0f;
                throwFlashBomb = true;
            }
        }

        this.transform.Translate(direction * 4.0f * Time.deltaTime);
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.tag == "Player" || other.gameObject.tag == "Power")
        {
            bossClear = true;
        }
    }
}
