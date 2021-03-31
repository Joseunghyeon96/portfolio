using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{
    Transform mainCam;
    Rigidbody m_rigidbody;
    Animator animator;
    WireAction wireAction;

    float speed;

    Transform weapon;
    public Transform getItemParent;
    Vector3 ItemRotation;

    float AttackCooltime;
    float ObjectCooltime;
    
    void Start()
    {
        mainCam = transform.GetChild(1);
        m_rigidbody = GetComponent<Rigidbody>();
        animator = GetComponentInChildren<Animator>();
        animator.SetBool("Move", false);
        animator.SetBool("JumpAble", false);
        animator.SetBool("Dash", false);
        wireAction = GetComponent<WireAction>();

        weapon = GameObject.Find("Player_Weapon").transform;
        getItemParent = null;
        AttackCooltime = 0.0f;
        ObjectCooltime = 0;
    }

    void Update()
    {
        CooltimeManager();
        //Move();
        Attack();
    }

    public void Move()
    {
        if (!PlayerStats.Instance.isAlive)
        {
            m_rigidbody.velocity = Vector3.zero;
            return;
        }

        animator.SetBool("Dash", false);
        animator.SetBool("Move", false);


        // --------------------------------------------------------

        // wire를 사용중인 경우
        if (wireAction.IsWireAction())
        {
            animator.SetBool("JumpAble", false);        // 와이어를 사용할 때 애니메이션. 이건 아직 적용안됨.
            return;
        }
        else animator.SetBool("JumpAble", true);

        // wire탄 후 슬라이딩 중인 경우
        if (wireAction.IsSliding()) return;

        // 이동 속도
        speed = 10.0f;

        // 달리기
        if (Input.GetKey(KeyCode.LeftShift))
        {
            speed *= 1.6f;
            animator.SetBool("Dash", true);
        }

        // Ground에서의 이동
        Vector3 curVelocity = m_rigidbody.velocity;

        curVelocity.x = 0.0f;
        curVelocity.z = 0.0f;
        m_rigidbody.velocity = curVelocity;

        Vector3 addVelocity = Vector3.zero;
        if (Input.GetKey(KeyCode.W))
            addVelocity += (transform.forward);
        if (Input.GetKey(KeyCode.S))
            addVelocity += (-transform.forward);
        if (Input.GetKey(KeyCode.A))
            addVelocity += (-transform.right);
        if (Input.GetKey(KeyCode.D))
            addVelocity += (transform.right);

        addVelocity = addVelocity.normalized * speed;
        m_rigidbody.velocity += addVelocity;


        if (addVelocity.x != 0.0f || addVelocity.z != 0.0f)
        {
            animator.SetBool("Move", true);

            // 플레이어가 이동하는 방향으로 회전
            this.transform.GetChild(0).rotation = Quaternion.Slerp(this.transform.GetChild(0).rotation, Quaternion.LookRotation(addVelocity), 0.6f);
        }
        
    }

    void Attack()
    {
        if (!PlayerStats.Instance.isAlive) return;

        if (Input.GetMouseButtonDown(0) && AttackCooltime <= 0.0f)
        {
            PlayerAudioSources.Instance.Play(PlayerAudioSources.State.ATTACK);
            animator.Play("Attack");
            AttackCooltime = 0.5f;
            // 무기를 한번 휘두를 때 한번만 공격
            if (getItemParent)
                weapon.GetChild(0).GetComponent<Weapon>().hitAble = true;
        }

        if(AttackCooltime <= 0.0f && getItemParent)
        {
            weapon.GetChild(0).GetComponent<Weapon>().hitAble = false;
        }

    }
    
    void CooltimeManager()
    {
        if (AttackCooltime > 0.0f)
            AttackCooltime -= Time.deltaTime;
        
        if (ObjectCooltime > 0.0f)
            ObjectCooltime -= Time.deltaTime;
    }


    private void OnCollisionStay(Collision other)
    {

        if (Input.GetKeyDown(KeyCode.F) && getItemParent && ObjectCooltime <= 0)
        {
            PlayerAudioSources.Instance.Play(PlayerAudioSources.State.PUTDOWNWEAPON);
            // 손의 무기를 맵으로 다시 돌려둠
            Vector3 position = transform.position + transform.forward * 3.0f;
            position.y = 0.2f;
            ItemRotation.y = transform.rotation.y;
            weapon.GetChild(0).position = position;
            weapon.GetChild(0).eulerAngles = ItemRotation;
            weapon.GetChild(0).gameObject.tag = "Object";
            weapon.GetChild(0).SetParent(getItemParent);
            getItemParent = null;

            ObjectCooltime = 0.2f;
        }
    }

    private void OnTriggerStay(Collider other)
    {

        if (other.gameObject.tag == "Object" && Input.GetKeyDown(KeyCode.F) && !getItemParent && ObjectCooltime <= 0)
        {
            PlayerAudioSources.Instance.Play(PlayerAudioSources.State.PICKUPWEAPON);
            // 맵의 무기를 손으로 가져옴
            ItemRotation = other.transform.rotation.eulerAngles;
            getItemParent = other.transform.parent;
            other.transform.SetParent(weapon);
            other.transform.localPosition = Vector3.zero;
            other.transform.localEulerAngles = Vector3.zero;
            other.gameObject.tag = "Item";

            ObjectCooltime = 0.2f;
        }
    }
}