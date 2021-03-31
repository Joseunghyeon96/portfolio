using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Room_Move : MonoBehaviour
{
    Animator animator;

    public bool do_costume;

    void Start()
    {
        animator = GetComponent<Animator>();
        do_costume = false;
    }

    void Update()
    {
        animator.SetBool("run", false);
        if (do_costume) return;

        if (Input.GetKey(KeyCode.UpArrow))
        {
            this.transform.Translate(Vector3.forward * 3.0f * Time.deltaTime);
            this.transform.rotation = Quaternion.Euler(0, 0, 0);
            if (Input.GetKey(KeyCode.LeftArrow)) this.transform.rotation = Quaternion.Euler(0, -45, 0);
            if (Input.GetKey(KeyCode.RightArrow)) this.transform.rotation = Quaternion.Euler(0, 45, 0);
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.DownArrow))
        {
            this.transform.Translate(Vector3.forward * 3.0f * Time.deltaTime);
            this.transform.rotation = Quaternion.Euler(0, 180, 0);
            if (Input.GetKey(KeyCode.LeftArrow)) this.transform.rotation = Quaternion.Euler(0, -135, 0);
            if (Input.GetKey(KeyCode.RightArrow)) this.transform.rotation = Quaternion.Euler(0, 135, 0);
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.LeftArrow))
        {
            this.transform.Translate(Vector3.forward * 3.0f * Time.deltaTime);
            if (!Input.GetKey(KeyCode.UpArrow) && !Input.GetKey(KeyCode.DownArrow))
                this.transform.rotation = Quaternion.Euler(0, -90, 0);
            animator.SetBool("run", true);
        }
        if (Input.GetKey(KeyCode.RightArrow))
        {
            this.transform.Translate(Vector3.forward * 3.0f * Time.deltaTime);
            if (!Input.GetKey(KeyCode.UpArrow) && !Input.GetKey(KeyCode.DownArrow))
                this.transform.rotation = Quaternion.Euler(0, 90, 0);
            animator.SetBool("run", true);
        }
    }
   
    void OnCollisionEnter(Collision other)
    {
        if (other.gameObject.tag == "Partner1")
        {
            GameObject.Find("UIController").GetComponent<Room_UIController>().meetPartner1 = true;
        }

        if (other.gameObject.tag == "Partner2")
        {
            GameObject.Find("UIController").GetComponent<Room_UIController>().meetPartner2 = true;
        }

        if (other.gameObject.tag == "Stage1")
        {
            SceneManager.LoadScene("Stage1");
            GameObject.Find("DataController").GetComponent<DataController>().Set_curStage(1);
        }

        if (other.gameObject.tag == "Stage2")
        {
            SceneManager.LoadScene("Stage2");
            GameObject.Find("DataController").GetComponent<DataController>().Set_curStage(2);
        }

        if (other.gameObject.tag == "Stage3")
        {
            SceneManager.LoadScene("Stage3");
            GameObject.Find("DataController").GetComponent<DataController>().Set_curStage(3);
        }
    }

    void OnCollisionExit(Collision other)
    {
        if (other.gameObject.tag == "Partner1")
        {
            GameObject.Find("UIController").GetComponent<Room_UIController>().meetPartner1 = false;
        }

        if (other.gameObject.tag == "Partner2")
        {
            GameObject.Find("UIController").GetComponent<Room_UIController>().meetPartner2 = false;
        }
    }

}
