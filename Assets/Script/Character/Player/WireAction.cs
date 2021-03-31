using System.Collections;
using System.Collections.Generic;
using UnityEngine;



public class WireAction : MonoBehaviour
{
    public float speed;
    public float wireActionSpeed = 0.2f;
    public float gravity;

    GameObject Camera;
    float rotSpeed = 1.0f; //ADD

    bool qWire;
    bool eWire;
    bool isSliding;
    bool isGround;
    bool firstWireForce;
    GameObject leftWire;
    GameObject rightWire;

    Vector3 preLeftWireLength;

    Rigidbody m_rigidbody;

    // Start is called before the first frame update
    void Start()
    {
        m_rigidbody = this.GetComponent<Rigidbody>();
        qWire = false;
        eWire = false;
        isSliding = false;
        firstWireForce = true;
        isGround = true;

        Camera = GameObject.Find("Main Camera");
        leftWire = GameObject.Find("LeftWire");
        rightWire = GameObject.Find("RightWire");

        preLeftWireLength = Vector3.zero;
    }

    // Update is called once per frame
    void Update()
    {
        SetWireAction();
        transform.rotation = Quaternion.Euler(0.0f, Camera.transform.eulerAngles.y, 0.0f);

        if (!qWire && !eWire && isGround)
            PlayerMovement_NUseWire();

        else
            PlayerMovement_UseWire();

    }

    void PlayerMovement_NUseWire()
    {
        if (qWire || eWire) return;

        Vector3 curVelocity = m_rigidbody.velocity;
        

        if (isSliding)
        {
            if (curVelocity.x + curVelocity.z < 10.0f)
                isSliding = false;

            return;
        }

        // Player의 Update에서 실행하면 실행순서 문제때문에 버그 발생해서 두고 나중에 해결하겠음
        GetComponent<Player>().Move();

        // 이동 관련 -> Player 스크립트 Move()의 Ground에서의 이동으로 옮김
    }

    void PlayerMovement_UseWire()
    {
        if (!qWire && !eWire) return;

        if (firstWireForce)
        {
            float jumpForce = (leftWire.transform.position.y - this.transform.position.y);
            if (jumpForce > 10.0f)
                jumpForce = 10.0f;
            m_rigidbody.AddForce(new Vector3(0.0f, jumpForce, 0.0f), ForceMode.VelocityChange);
            firstWireForce = false;
        }

        m_rigidbody.constraints = RigidbodyConstraints.None;


        Vector3 wireForce = new Vector3(0.0f, 0.0f, 0.0f);
        if (qWire)
        {
            isSliding = true;
            isGround = false;

            wireForce = (leftWire.transform.position - this.transform.position).normalized;
        }

        if (eWire)
        {
            isSliding = true;
            isGround = false;

            wireForce += (rightWire.transform.position - this.transform.position).normalized;
        }

        wireForce = wireForce.normalized * wireActionSpeed;
        wireForce.y *= 2.0f;
        m_rigidbody.AddForce(wireForce, ForceMode.VelocityChange);

        // 캐릭터 모델을 벽을 향해 회전
        Vector3 CharactorDirect = wireForce;
        CharactorDirect.y = 0;
        this.transform.GetChild(0).rotation = Quaternion.Slerp(this.transform.GetChild(0).rotation, Quaternion.LookRotation(CharactorDirect), 0.6f);


    }

    void SetWireAction()
    {
        qWire = leftWire.GetComponent<wire>().isGrabWall;
        eWire = rightWire.GetComponent<wire>().isGrabWall;
        if (!qWire&&!eWire) firstWireForce = true;
    }

    public bool IsWireAction()
    {
        if (qWire || eWire)
            return true;

        return false;
    }

    public bool IsSliding()
    {
        if (isSliding)
            return true;

        return false;
    }


    private void OnCollisionEnter(Collision collision)
    {

        if (collision.gameObject.tag == "Ground")
        {

            if (!qWire && !eWire)
            {
                isGround = true;
            }
        }

        if (collision.gameObject.tag == "Wall")
        {

            if (!qWire && !eWire)
                isGround = true;
        }
    }
    private void OnCollisionStay(Collision collision)
    {
        if (collision.gameObject.tag == "Ground")
        {
            if (!qWire && !eWire)
                isGround = true;
        }
    }
}
