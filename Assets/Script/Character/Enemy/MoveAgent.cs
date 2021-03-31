using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

[RequireComponent(typeof(NavMeshAgent))]
public class MoveAgent : MonoBehaviour
{
    public List<Transform> wayPoints;
    public int nextIdx = 0;

    private NavMeshAgent agent;
    private EnemyStat enemyStat;
    private Transform enemy;
    private Transform player;

    private readonly float patrollSpeed = 1.5f;
    private readonly float traceSpeed = 4.0f;

    private float damping = 1.0f;
    private bool _patrolling;

    public bool patrolling
    {
        get { return _patrolling; }
        set
        {
            _patrolling = value;
            if (_patrolling)
            {
                agent.speed = patrollSpeed;
                damping = 1.0f;
                MoveWayPoint();
            }
        }
    }

    public bool tracing;
    private Vector3 _traceTarget;
    public Vector3 traceTarget
    {
        get { return _traceTarget; }
        set
        {
            _traceTarget = value;
            agent.speed = traceSpeed;
            damping = 7.0f;
            TraceTarget(_traceTarget);
        }
    }

    public float speed
    {
        get { return agent.velocity.magnitude; }
    }

    void TraceTarget(Vector3 pos)
    {
        if (agent.isPathStale) return;
        agent.destination = pos;
        agent.isStopped = false;
    }

    private void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player").GetComponent<Transform>();
        enemy = GetComponent<Transform>();
        enemyStat = GetComponent<EnemyStat>();
        agent = GetComponent<NavMeshAgent>();
        agent.autoBraking = false;
        agent.updateRotation = false;
        agent.speed = patrollSpeed;

        //var group = GameObject.Find("WayPointGroup");
        var group = GameObject.Find("SpawnPoints");

        if (group != null)
        {
            group.GetComponentsInChildren<Transform>(wayPoints);
            wayPoints.RemoveAt(0);
            nextIdx = Random.Range(0, wayPoints.Count);
        }

        MoveWayPoint();
    }

    private void MoveWayPoint()
    {
        if (agent.isPathStale) return;
        agent.destination = wayPoints[nextIdx].position;
        agent.isStopped = false;
    }

    public void Stop()
    {
        agent.isStopped = true;
        agent.velocity = Vector3.zero;
        _patrolling = false;
    }

    Quaternion rot;
    public void Update()
    {
        if (enemyStat.isAlive == false) return;

        if(tracing) rot = Quaternion.LookRotation(player.position - enemy.position);
        else if(agent.isStopped == false) rot = Quaternion.LookRotation(agent.destination - enemy.position);
        enemy.rotation = Quaternion.Slerp(enemy.rotation, rot, Time.deltaTime * damping);

        if (!_patrolling) return;

        if (agent.velocity.sqrMagnitude >= 0.2f * 0.2f && agent.remainingDistance <= 0.5f)
        {
            nextIdx = ++nextIdx % wayPoints.Count;
            MoveWayPoint();
        }
    }

}
